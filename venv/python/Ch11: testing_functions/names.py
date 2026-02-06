from name_function import *
import unittest

class NamesTestCases(unittest.TestCase):

    def test_first_last_name(self):
        formatted_name = get_formatted_name('john', 'doe')
        self.assertEqual(formatted_name, 'John Doe')


    def test_full_name(self):
        formatted_name = get_formatted_full_name('john', 'jane', 'doe')
        self.assertEqual(formatted_name, 'John Jane Doe')


if __name__ == '__main__':
    unittest.main()