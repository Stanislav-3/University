from units.map.graph import Graph
from units.car import Car
from units.driver import Driver
from units.budget import Budget
from units.order.order import Order


units = {
    'map': Graph,
    'car': Car,
    'driver': Driver,
    'budget': Budget,
    'order': Order,
}


def create_unit(unit: str, *args):
    unit = units.get(unit.lower(), None)
    if unit is None:
        raise ValueError(f'Item {unit} cannot be created!')

    if len(args):
        return unit(*args)
    else:
        return unit()