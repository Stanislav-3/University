import numpy as np
import scipy
import sympy as sp
import matplotlib
import matplotlib.pyplot as plt
from scipy.stats import weibull_min
from matplotlib.widgets import Slider, TextBox
from pierson import get_chi2_and_pValue
import moments
from info import f, N
from task1 import get_plot_data1, generate_Y1, set_F_get_params
from task2 import get_plot_data2


matplotlib.use('Qt5Agg')

slider_1, slider_2 = None, None
params = None
f_x = None


def update_texts(*args, alpha=0.05, eps=5):
    if task_number == '1':
        points = generate_Y1(*args)
    else:
        points = get_plot_data2(*args)['empirical']

    analytical_e, analytical_std = None, None
    if task_number == '2':
        analytical_e, analytical_std = moments.get_analytical_moments(*args)
        analytical_E_TextBox.set_val(f'{round(analytical_e, eps)}')
        analytical_S_TextBox.set_val(f'{round(analytical_std, eps)}')
    else:
        # analytical_e, analytical_std = moments.get_theoretical_moments(f_x, *args)
        analytical_E_TextBox.set_val(f'-')
        analytical_S_TextBox.set_val(f'-')


    empirical_e, empirical_std = moments.get_empirical_moments(points)

    empirical_E_TextBox.set_val(f'{round(empirical_e, eps)}')
    empirical_S_TextBox.set_val(f'{round(empirical_std, eps)}')

    gamma = 1.0 - alpha
    delta = empirical_std * scipy.stats.t.ppf(gamma, len(points) - 1) / np.sqrt(len(points) - 1)
    sl_E_TextBox.set_val(f'SL:{gamma} | {round(empirical_e - delta, eps)} <= Ex <= {round(empirical_e + delta, eps)}')

    l = ((len(points) - 1) * empirical_std) / scipy.stats.chi2.ppf(1 - alpha / 2, len(points) - 1)
    r = ((len(points) - 1) * empirical_std) / scipy.stats.chi2.ppf(alpha / 2, len(points) - 1)

    sl_S2_TextBox.set_val(f'SL:{gamma} | {round(l, eps)} <= Sx <= {round(r, eps)}')

    bins = int(np.sqrt(N)) if N < 100 else int(2 * 3 * 4 * np.log(N))

    if task_number == '2':
        chi2, p_value = get_chi2_and_pValue(task_number, points, *args, bins=bins)
        pierson_TextBox.set_val(f'chi2: {round(chi2, 4)}; p-value: {p_value}')
    else:
        pierson_TextBox.set_val(f'chi2: -; p-value: -')


def update(val):
    args = []
    if slider_1 is not None:
        args.append(float(slider_1.val))
    if slider_2 is not None:
        args.append(float(slider_2.val))

    if task_number == '1':
        plot_data = get_plot_data1(*args)
    else:
        plot_data = get_plot_data2(*args)

    ax.cla()
    if task_number == '2':
        ax.plot(*plot_data['analytical'], label="Analytical", color="red")

    ax.hist(plot_data['empirical'], bins=10 * 5, density=True, histtype='step', label='Empirical')

    update_texts(*args)

    fig.canvas.draw_idle()


def plot(*args):
    # matplotlib.backends.backend_qt5
    # Plot
    global fig, ax, theory_line, empirical_hist, slider_1, slider_2

    fig, ax = plt.subplots()
    plt.subplots_adjust(left=0.1, bottom=0.25)

    if task_number == '1':
        plot_data = get_plot_data1(*args)
    else:
        plot_data = get_plot_data2(*args)

        # Theoretical
        theory_line, *_ = ax.plot(*plot_data['analytical'], label="Analytical", color="red")

    # Computational
    empirical_hist = ax.hist(plot_data['empirical'], bins=10 * 5, density=True, histtype='step', label='Empirical')

    # Interactive tools
    global slider_1, slider_2

    if len(params) > 0:
        slider_1 = Slider(ax=plt.axes([0.1, 0.15, 0.8, 0.03]), label=f'{params[0]} = ', valmin=1, valmax=10, valinit=args[0])

    if len(params) > 1:
        slider_2 = Slider(ax=plt.axes([0.1, 0.10, 0.8, 0.03]), label=f'{params[1]} = ', valmin=1, valmax=10, valinit=args[1])

    global analytical_E_TextBox, analytical_S_TextBox, empirical_E_TextBox, empirical_S_TextBox, \
        sl_E_TextBox, sl_S2_TextBox, pierson_TextBox

    analytical_E_TextBox = TextBox(ax=plt.axes([0.15, 0.05, 0.1, 0.03]), label='Analytical E ', initial='1')
    analytical_S_TextBox = TextBox(ax=plt.axes([0.4, 0.05, 0.1, 0.03]), label='Analytical S ', initial='2')
    empirical_E_TextBox = TextBox(ax=plt.axes([0.15, 0.0, 0.1, 0.03]), label='Empirical E ', initial='3')
    empirical_S_TextBox = TextBox(ax=plt.axes([0.4, 0.0, 0.1, 0.03]), label='Empirical S ', initial='4')

    sl_E_TextBox = TextBox(ax=plt.axes([0.55, 0.05, 0.44, 0.03]), label='', initial='5')
    sl_S2_TextBox = TextBox(ax=plt.axes([0.55, 0.0, 0.44, 0.03]), label='', initial='6')

    pierson_TextBox = TextBox(ax=plt.axes([0.35, 0.9, 0.4, 0.03]), label='Pierson chi2 criterion ', initial='7')

    if slider_1 is not None:
        slider_1.on_changed(update)

    if slider_2 is not None:
        slider_2.on_changed(update)

    update_texts(*args)

    plt.legend()
    plt.show()


# task_number = input('What task to run? (type 1 or 2): ')
task_number = '2'
if task_number == '1':
    # F_x = input('Input F(x):')
    # F_x = '1 - x^(-3) + log(x, 2)'
    F_x = '1 - exp(-a * x)'

    # F_x = '(x - a) / (b - a)'

    params = set_F_get_params(F_x)
    print(params)
    f_x = sp.diff(sp.sympify(F_x), sp.Symbol('x'))
    f_x = sp.lambdify(sp.symbols('x,' + ','.join(params)), f_x)

    # print(sp.symbols('x,' + ','.join(params)))
    # print(f_x(4, 1, 3))
    # exit(0)
    args = [1.]
    args += [1.1] * (len(params) - 1)

else:
    args = [1, 1]
    params = ['k', 'λ']

plot(*args)
