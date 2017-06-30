import ground_station

import unittest

class TestChecksum(unittest.TestCase):
    def setUp(self):
        pass

    def tearDown(self):
        pass

    def test_1(self):
        data = [0x83, 0xff]
        checksum = ground_station.getChecksum(data)
        self.assertEqual(checksum, 0x7c)


if __name__ == "__main__":
    unittest.main()