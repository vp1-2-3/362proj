import tkinter as tk
import math

class CalculatorButtons:
    def __init__(self, root, calculator):
        self.root = root
        self.calculator = calculator
        self.buttons = [
            '7', '8', '9', '/', 
            '4', '5', '6', '%',
            '1', '2', '3', '*',
            '0', '.', '=', '-',
            'log','sin', 'cos','+', 
            'ln', 'Bin', 'Hex','History',
            'C-H','Clear'
        ]
        self.create_buttons()

    def create_buttons(self):
        '''Creates the buttons for the calculator'''
        
        row_val = 1
        col_val = 0
        for button in self.buttons:
            if button == '=':
                btn = tk.Button(self.root, text=button, padx=30, pady=25, command=self.calculator.calculate)
            elif button in ('sin', 'cos', 'log', 'ln'):
                btn = tk.Button(self.root, text=button, padx=25, pady=25, command=lambda button=button: self.calculator.trig_log_function(button))
            elif button == 'History':
                btn = tk.Button(self.root, text=button, padx=15, pady=25, command=self.calculator.open_history)
            elif button == 'Bin':
                btn = tk.Button(self.root, text=button, padx=25, pady=25, command=self.calculator.convert_binary)
            elif button == 'Hex':
                btn = tk.Button(self.root, text=button, padx=25, pady=25, command=self.calculator.convert_hexadecimal)
            elif button == 'Clear':
                btn = tk.Button(self.root, text = button, padx=25, pady=25, command=self.calculator.clear)
            elif button == 'C-H':
                btn = tk.Button(self.root, text = button, padx=25, pady=25, command=self.calculator.h_clear)
            else:
                btn = tk.Button(self.root, text=button, padx=30, pady=25, command=lambda button=button: self.calculator.button_click(button))

            btn.grid(row=row_val, column=col_val, sticky="nsew")
            self.root.grid_columnconfigure(col_val, weight=1)
            self.root.grid_rowconfigure(row_val, weight=1)
            col_val += 1
            if col_val > 3:
                col_val = 0
                row_val += 1

class Calculator:
    def __init__(self, root):
        self.root = root
        self.root.title("Calculator")

        self.entry = tk.Entry(root, width=30, borderwidth=10)
        self.entry.grid(row=0, column=0, columnspan=4, sticky="nsew")

        self.buttons = CalculatorButtons(root, self)

        self.history = []  # Initialize an empty list for history log

        root.resizable(True, True)

        for i in range(1, 6):
            root.grid_rowconfigure(i, weight=1)
        for i in range(4):
            root.grid_columnconfigure(i, weight=1)

    def button_click(self, value):
        '''When button click called'''
        
        current = self.entry.get()
        self.entry.delete(0, tk.END)
        self.entry.insert(0, current + str(value))

    def clear(self):
        '''Clears the display bar'''
        
        self.entry.delete(0, tk.END)

    def calculate(self):
        '''Calculates arithmetic operations'''
        
        current = self.entry.get()
        try:
            result = eval(current)
            self.history.append(current + ' = ' + str(result))
            self.entry.delete(0, tk.END)
            self.entry.insert(0, result)
        except:
            self.entry.delete(0, tk.END)
            self.entry.insert(0, "Error")

    def trig_log_function(self, function):
        '''Calculates output trigonometric buttons'''
        
        current = self.entry.get()
        try:
            if function == 'sin':
                result = math.sin(eval(current))
            elif function == 'cos':
                result = math.cos(eval(current))
            elif function == 'log':
                result = math.log10(eval(current))
            elif function == 'ln':
                result = math.log(eval(current))
            self.history.append(function + '(' + current + ') = ' + str(result))
            self.entry.delete(0, tk.END)
            self.entry.insert(0, result)
        except:
            self.entry.delete(0, tk.END)
            self.entry.insert(0, "Error")

    def convert_hexadecimal(self):
        '''Converts input to hexadecimal'''
        try:
            current = self.entry.get()
            decimal_value = eval(current)
            hexadecimal_value = hex(decimal_value)[2:]
            self.history.append(f'{current} in hexadecimal: {hexadecimal_value}')
            self.entry.delete(0, tk.END)
            self.entry.insert(0, hexadecimal_value)
        except:
            self.entry.delete(0, tk.END)
            self.entry.insert(0, "Error")
            
    def convert_binary(self):
        '''Converts input to binary'''
        try:
            current = self.entry.get()
            decimal_value = eval(current)
            binary_value = bin(decimal_value)[2:]
            self.history.append(f'{current} in binary: {binary_value}')
            self.entry.delete(0, tk.END)
            self.entry.insert(0, binary_value)
        except:
            self.entry.delete(0, tk.END)
            self.entry.insert(0, "Error")
            
    def print_to_file(self):
        '''Writes the output to history'''
        
        with open('calculator_history.txt', 'w') as f:
            for i in self.history:
                f.write("%s\n" % i)
                
    def h_clear(self):
        '''Clears the History'''
        
        self.history = []
        
    def open_history(self):
        '''Opens the history log'''
        
        new_window = tk.Toplevel(self.root)
        new_window.title("History Log")
        log_text = tk.Text(new_window, height=20, width=40)
        log_text.pack()
        log_text.insert(tk.END, "\n".join(self.history))
        print_button = tk.Button(new_window, text='Print to File', padx=5, pady=5, command=self.print_to_file)
        print_button.pack()

if __name__ == "__main__":
    root = tk.Tk()
    app = Calculator(root)
    root.mainloop()