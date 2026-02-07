import unittest
from survey import AnonymousSurvey

class TestSurvery(unittest.TestCase):

    def test_store_single_response(self):
        question = 'what language did you first learn'
        my_survery = AnonymousSurvey(question)
        my_survery.store_response("english")
        self.assertIn('english', my_survery.responses)


if __name__ == '__main__':
    unittest.main()


