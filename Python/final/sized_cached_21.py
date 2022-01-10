from inspect import getfullargspec


def cached_with_size(size: int):
    def cached(func):
        cache = []
        results = {}

        def resulting_func(*args, **kwargs):
            full_arg_spec = getfullargspec(func)
            named_args = full_arg_spec[0]
            arguments = {}

            kwargs_ = dict(kwargs)

            args_len = len(args)
            for i in range(min(len(named_args), args_len)):
                arguments[named_args[i]] = args[i]

            while len(named_args) - args_len > 0:
                arguments[named_args[args_len]] = kwargs[named_args[args_len]]
                del kwargs_[named_args[args_len]]
                args_len += 1

            if full_arg_spec[1] is not None:
                arguments['*args'] = args[len(named_args):]

            if full_arg_spec[2] is not None:
                arguments['**kwargs'] = kwargs_

            if len(arguments) > size:
                return 'Over size'

            if arguments in cache:
                output = 'Cached: '
                res = results[cache.index(arguments)]
            else:
                output = 'Not cached: '
                res = func(*args, **kwargs)
                cache.append(arguments)
                results[len(cache) - 1] = res
            return output + f'{res}'

        return resulting_func

    return cached
