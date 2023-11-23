import unittest


class UselessTestCase(unittest.TestCase):
    def test_loading_works(self):
        try:
            import mcpltool
        except ImportError:
            self.fail("Could not import mcpltool")


if __name__ == '__main__':
    unittest.main()
