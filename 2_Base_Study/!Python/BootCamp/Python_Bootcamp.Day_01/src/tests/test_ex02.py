import pytest
from contextlib import nullcontext as dnr
from ex02 import add_ingot, get_ingot, empty


class TestPurse:
    @pytest.mark.parametrize(
        "in_ingot, out_ingot, expectation",
        [
            (list(), list(), pytest.raises(Exception)),
            (dict(gold_ingots=1), dict(gold_ingots=2), dnr()),
            (dict(gold_ingots=1), dict(gold_ingots='2'), pytest.raises(Exception)),
            (dict(), dict(gold_ingots=1), dnr()),
            (dict(some=1), dict(some=1, gold_ingots=1), dnr())
        ]
    )
    def test_add_ingot(self, in_ingot, out_ingot, expectation):
        with expectation:
            assert add_ingot(in_ingot) == out_ingot

    @pytest.mark.parametrize(
        "in_ingot, out_ingot, expectation",
        [
            (list(), list(), pytest.raises(Exception)),
            (dict(gold_ingots=1), dict(gold_ingots=0), dnr()),
            (dict(gold_ingots=-1), dict(), pytest.raises(Exception)),
            (dict(gold_ingots=2, some=3), dict(gold_ingots=1, some=3), dnr()),
            (dict(gold_ingots=1, some=3), dict(gold_ingots=0, some=3), dnr()),
        ]
    )
    def test_get_ingot(self, in_ingot, out_ingot, expectation):
        with expectation:
            assert get_ingot(in_ingot) == out_ingot
    
    @pytest.mark.parametrize(
        "in_ingot, out_ingot, expectation",
        [
            (list(), list(), pytest.raises(Exception)),
            (dict(gold_ingots=1), dict(), dnr()),
            (dict(gold_ingots=-1), dict(), pytest.raises(Exception)),
            (dict(gold_ingots=2, some=3), dict(), dnr()),
        ]
    )
    def test_empty(self, in_ingot, out_ingot, expectation):
        with expectation:
            assert empty(in_ingot) == out_ingot


    @pytest.mark.parametrize(
        "in_ingot, out_ingot, expectation",
        [
            (dict(gold_ingots=1, some=1), dict(gold_ingots=1), dnr()),
            (dict(gold_ingots=-1), dict(), pytest.raises(Exception)),
        ]
    )
    def test_complex(self, in_ingot, out_ingot, expectation):
        with expectation:
            assert add_ingot(get_ingot(empty(in_ingot))) == out_ingot