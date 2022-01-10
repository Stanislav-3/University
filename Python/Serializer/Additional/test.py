import pytest
from functions import *


class TestSimple:
    res = 3
    not_cached = f'Not cached: {res}'
    cached = f'Cached: {res}'

    def test_1(self):
        assert simple_func(1, 2) == self.not_cached

    def test_2(self):
        assert simple_func(1, 2) == self.cached

    def test_3(self):
        assert simple_func(1, y=2) == self.cached

    def test_4(self):
        assert simple_func(x=1, y=2) == self.cached

    def test_5(self):
        assert simple_func(y=2, x=1) == self.cached


class TestFull:
    res = 3
    not_cached = f'Not cached: {res}'
    cached = f'Cached: {res}'

    def test_1(self):
        assert full_func(1, 2) == self.not_cached

    def test_2(self):
        assert full_func(2, 1) == self.not_cached

    def test_3(self):
        assert full_func(1, y=2) == self.not_cached

    def test_4(self):
        assert full_func(x=1, y=2) == self.not_cached

    def test_5(self):
        assert full_func(y=2, x=1) == self.cached

    def test_6(self):
        assert full_func(0, 2, -2, y=2, x=1) == self.not_cached

    def test_7(self):
        assert full_func(0, 2, -2, x=1, y=2) == self.cached


class TestCompound:
    res = 3
    not_cached = f'Not cached: {res}'
    cached = f'Cached: {res}'

    def test_1(self):
        assert compound_func(1, 2) == self.not_cached

    def test_2(self):
        assert compound_func(1, 2) == self.cached

    def test_3(self):
        assert compound_func(1, y=2) == self.cached

    def test_4(self):
        assert compound_func(x=1, y=2) == self.cached

    def test_5(self):
        assert compound_func(y=2, x=1) == self.cached

    def test_6(self):
        assert compound_func(1, 1, 1) == self.not_cached

    def test_7(self):
        assert compound_func(1, 1, new=1) == self.not_cached

    def test_8(self):
        assert compound_func(1, 0, 1, new=1) == self.not_cached
