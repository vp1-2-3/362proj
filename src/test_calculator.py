import unittest
from tkinter import Tk
from calc import Calculator

class TestCalculator(unittest.TestCase):
    def setUp(self):
        # Create an instance of Calculator for testing
        self.root = Tk()
        self.calculator = Calculator(self.root)

    def test_button_click(self):
        # Test the button_click method
        self.calculator.button_click(7)
        self.assertEqual(self.calculator.entry.get(), '7')

    def test_clear(self):
        # Test the clear method
        self.calculator.entry.insert(0, '123')
        self.calculator.clear()
        self.assertEqual(self.calculator.entry.get(), '')

    def test_calculate(self):
        # Test the calculate method
        self.calculator.entry.insert(0, '2+3')
        self.calculator.calculate()
        self.assertEqual(self.calculator.entry.get(), '5')

    def test_trig_log_function_sin(self):
        # Test the trig_log_function method for sin
        self.calculator.entry.insert(0, '45')
        self.calculator.trig_log_function('sin')
        self.assertEqual(round(float(self.calculator.entry.get()), 4), 0.8509)

    def test_trig_log_function_cos(self):
        # Test the trig_log_function method for cos
        self.calculator.entry.insert(0, '60')
        self.calculator.trig_log_function('cos')
        self.assertEqual(round(float(self.calculator.entry.get()), 4), -.9524)

    def test_convert_hexadecimal(self):
        # Test the convert_hexadecimal method
        self.calculator.entry.insert(0, '255')
        self.calculator.convert_hexadecimal()
        self.assertEqual(self.calculator.entry.get(), 'ff')

    def test_convert_binary(self):
        # Test the convert_binary method
        self.calculator.entry.insert(0, '10')
        self.calculator.convert_binary()
        self.assertEqual(self.calculator.entry.get(), '1010')

    def test_open_history(self):
        # Test the open_history method
        self.calculator.history = ['2+3 = 5', 'sin(45) = 0.8509']
        self.calculator.open_history()
        self.assertTrue(self.calculator.history)

    # Add more test methods for other functionalities

    def tearDown(self):
        # Clean up after each test
        self.root.destroy()

if __name__ == '__main__':
    unittest.main()
