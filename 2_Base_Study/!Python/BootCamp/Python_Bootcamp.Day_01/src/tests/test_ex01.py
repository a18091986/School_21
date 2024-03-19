import pytest
from contextlib import nullcontext as dnr
from ex00 import add_ingot, get_ingot, empty
from ex01 import split_booty


class TestPurse:
    @pytest.mark.parametrize(
        "iningot1, iningot2, iningot3, outingot1, outingot2, outingot3, expectation",
        [
            (
                dict(gold_ingots=1), dict(gold_ingots=2), dict(gold_ingots=2), 
                dict(gold_ingots=2), dict(gold_ingots=2), dict(gold_ingots=1), 
                dnr()
            ),
            (
                dict(gold_ingots='1'), dict(gold_ingots=2), dict(gold_ingots=2), 
                dict(gold_ingots=2), dict(gold_ingots=2), dict(gold_ingots=1), 
                pytest.raises(Exception)
            ),
            (
                dict(gold_ingots=-1), dict(gold_ingots=2), dict(gold_ingots=2), 
                dict(gold_ingots=2), dict(gold_ingots=2), dict(gold_ingots=1), 
                pytest.raises(Exception)
            ),

        ]
    )
    def test_split_booty(self, iningot1, iningot2, iningot3, outingot1, outingot2, outingot3, expectation):
        with expectation:
            res1, res2, res3 = split_booty(iningot1, iningot2, iningot3)
            assert res1 == outingot1 or res2 == outingot2 or res3 == outingot3
