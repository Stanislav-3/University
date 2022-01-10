import enum


class Order_status(enum.Enum):
    All = 0
    Reserved = 1
    Canceled = 2
    Executing = 3
    Completed = 4