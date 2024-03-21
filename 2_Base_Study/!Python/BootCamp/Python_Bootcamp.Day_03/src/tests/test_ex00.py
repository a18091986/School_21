import pytest
from contextlib import nullcontext as dnr
from ex00 import Key

# AssertionError: len(key) == 1337
# AssertionError: key[404] == 3
# AssertionError: key > 9000
# AssertionError: key.passphrase == "zax2rulez"
# AssertionError: str(key) == "GeneralTsoKeycard"

class TestKey:
    @pytest.mark.parametrize(
        "in_length, in_val404, in_more_then, in_passphrase, in_repr, length, val404, more_then, passphrase, repr, expectation", 
        [
            (
                1337, 3, 9000, "zax2rulez", "GeneralTsoKeycard", 
                1337, 3, 9000, "zax2rulez", "GeneralTsoKeycard", dnr()
            ),

            (
                1337, 3, 9000, "zax2rulez", "GeneralTsoKeycard", 
                1337, 3, 9000, "zax2rulez1", "GeneralTsoKeycard", pytest.raises(AssertionError)
            ),
            
            (
                1337, 3, 9000, "zax2rulez", "GeneralTsoKeycard", 
                1338, 3, 9000, "zax2rulez1", "GeneralTsoKeycard",
                pytest.raises(AssertionError)
            ),

            (
                1337, 3, 9000, "zax2rulez", "GeneralTsoKeycard", 
                1337, 3, 9001, "zax2rulez1", "GeneralTsoKeycard",
                pytest.raises(AssertionError)
            ),

            (
                1337, 3, 9000, "zax2rulez", "GeneralTsoKeycard", 
                1337, 3, 9000, "zax2rulez1", "GeneralTsoKeycard3",
                pytest.raises(AssertionError)
            ),

            (
                1337, '3', 9000, "zax2rulez", "GeneralTsoKeycard", 
                1337, 3, 9000, "zax2rulez", "GeneralTsoKeycard",
                pytest.raises(TypeError)
            ),
        ]
    )
    def test_key(self, in_length: int, in_val404: int, in_more_then: int, in_passphrase: str, in_repr: str, length: int, val404: int, more_then: int, passphrase: str, repr: str, expectation):
        with expectation:
            key = Key(in_length, in_val404, in_more_then, in_passphrase, in_repr)
            assert len(key) == length
            assert key[404] == val404
            assert key > more_then
            assert key.passphrase == passphrase
            assert str(key) == repr

