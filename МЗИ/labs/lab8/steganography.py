import random
import numpy as np
from PIL import Image, ImageDraw, ImageFont
import matplotlib.pyplot as pyplot   


def _normalized_RGB(img):
    if img.dtype == np.uint8:
        return img[:,:,:3] / 255.
    else:
        return img[:,:,:3].astype(np.float64)


def _mix(a, b, u, keepImag = False):
    if keepImag:
        return (a.real * (1 - u) + b.real * u) + a.imag * 1j
    else:
        return a * (1 - u) + b * u


def _centralize(img, side = .06, clip = False):
    img = img.real.astype(np.float64)
    thres = img.size * side
    
    l = img.min()
    r = img.max()
    while l + 1 <= r:
        m = (l + r) / 2.
        s = np.sum(img < m)
        if s < thres:
            l = m
        else:
            r = m
    low = l            
            
    l = img.min()
    r = img.max()
    while l + 1 <= r:
        m = (l + r) / 2.
        s = np.sum(img > m)
        if s < thres:
            r = m
        else:
            l = m            
            
    high = max(low + 1, r)          
    img = (img - low) / (high - low)
    
    if clip:
        img = np.clip(img, 0, 1)
    
    return img, low, high


def _shuffle_gen(size, secret = None):
    r = np.arange(size)
    if secret:
        random.seed(secret)
        for i in range(size, 0, -1):
            j = random.randint(0, i)
            r[i-1], r[j] = r[j], r[i-1]
    return r


def _xmap_gen(shape, secret = None):
    xh, xw = _shuffle_gen(shape[0], secret), _shuffle_gen(shape[1], secret)
    xh = xh.reshape((-1, 1))
    return xh, xw


def _encode_image(oa, ob, xmap = None, margins = (1, 1), alpha = None):
    na = _normalized_RGB(oa)
    nb = _normalized_RGB(ob)
    fa = np.fft.fft2(na, None, (0, 1))
    pb = np.zeros((na.shape[0]//2-margins[0]*2, na.shape[1]-margins[1]*2, 3))
    pb[:nb.shape[0], :nb.shape[1]] = nb

    low = 0
    if alpha is None:
        _, low, high = _centralize(fa)
        alpha = (high - low)# / 2

    if xmap is None:
        xh, xw = _xmap_gen(pb.shape)
    else:
        xh, xw = xmap[:2]
        
    fa[+margins[0]+xh, +margins[1]+xw] += pb * alpha
    fa[-margins[0]-xh, -margins[1]-xw] += pb * alpha
    
    xa = np.fft.ifft2(fa, None, (0, 1))
    xa = xa.real
    xa = np.clip(xa, 0, 1)

    return xa, fa


def _encode_text(oa, text, *args, **kwargs):
    font = ImageFont.truetype("consolas.ttf", oa.shape[0] // 7)
    renderSize = font.getsize(text)
    padding = min(renderSize) * 2 // 10
    renderSize = (renderSize[0] + padding * 2, renderSize[1] + padding * 2)
    textImg = Image.new('RGB', renderSize, (0, 0, 0))
    draw = ImageDraw.Draw(textImg)
    draw.text((padding, padding), text, (255, 255, 255), font = font)
    ob = np.asarray(textImg)
    return _encode_image(oa, ob, *args, **kwargs)


def _decode_image(xa, xmap = None, margins = (1, 1), oa = None, full = False):
    na = _normalized_RGB(xa)
    fa = np.fft.fft2(na, None, (0, 1))
        
    if xmap is None:
        xh = _xmap_gen((xa.shape[0]//2-margins[0]*2, xa.shape[1]-margins[1]*2))
    else:
        xh, xw = xmap[:2]
        
    if oa is not None:
        noa = _normalized_RGB(oa)
        foa = np.fft.fft2(noa, None, (0, 1))
        fa -= foa
        
    if full:
        nb, _, _ = _centralize(fa, clip = True)
    else:
        nb, _, _ = _centralize(fa[+margins[0]+xh, +margins[1]+xw], clip = True)
    return nb


def _imshow_ex(img, *args, **kwargs):
    img, _, _ = _centralize(img, clip = True)
    
    kwargs["interpolation"] = "nearest"
    if "title" in kwargs:
        pyplot.title(kwargs["title"])
        kwargs.pop("title")
    if len(img.shape) == 1:
        kwargs["cmap"] = "gray"
    pyplot.imshow(img, *args, **kwargs)


def _imsave_ex(fn, img, *args, **kwargs):
    kwargs["dpi"] = 1
    
    if img.dtype != np.uint8:
        img, _, _ = _centralize(img, clip = True)
        img = (img * 255).round().astype(np.uint8)
        
    pyplot.imsave(fn, img, *args, **kwargs)


def encode(source, destination, secret, message):
    image = pyplot.imread(source)
    margins = (image.shape[0] // 7, image.shape[1] // 7)
    margins=(1, 1)
    xmap = _xmap_gen((image.shape[0] // 2 - margins[0] * 2, image.shape[1] - margins[1] * 2), secret)

    ea, _ = _encode_text(image, message, xmap, margins, None)
    _imsave_ex(destination, ea)


def decode(original, encoded, secret):
    oa = pyplot.imread(original)
    xa = pyplot.imread(encoded)
    margins=(1, 1)
    xmap = _xmap_gen((oa.shape[0] // 2 - margins[0] * 2, oa.shape[1] - margins[1] * 2), secret)
    xb = _decode_image(xa, xmap, margins, oa)

    pyplot.figure()
    pyplot.subplot(221)
    _imshow_ex(xa, title = "encoded")
    pyplot.subplot(222)
    _imshow_ex(xb, title = "decoded")
    pyplot.show() 
