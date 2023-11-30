import tkinter as tk
import math

class Calculator:
    def __init__(self, root):
        self.root = root
        self.root.title("Calculator")

        self.entry = tk.Entry(root, width=30
        , borderwidth=10)
        self.entry.grid(row=0, column=0, columnspan=4, sticky="nsew")

        self.buttons = [
            '7', '8', '9', '/',
            '4', '5', '6', '*',
            '1', '2', '3', '-',
            '0', ' . ', '=', '+',
            'sin', 'cos', 'log', 'ln',
            'History'
        ]

        row_val = 1
        col_val = 0

        for button in self.buttons:
            if button == '=':
                btn = tk.Button(root, text=button, padx=30, pady=25, command=self.calculate)
            elif button in ('sin', 'cos', 'log', 'ln'):
                btn = tk.Button(root, text=button, padx=25, pady=25, command=lambda button=button: self.trig_log_function(button))
            elif button == 'History':
                btn = tk.Button(root, text=button, padx=15, pady=25, command=self.open_new_window)
            else:
                btn = tk.Button(root, text=button, padx=30, pady=25, command=lambda button=button: self.button_click(button))

            btn.grid(row=row_val, column=col_val, sticky="nsew")
            
            # Make the buttons resizable
            root.grid_columnconfigure(col_val, weight=1)
            root.grid_rowconfigure(row_val, weight=1)
            
            col_val += 1
            if col_val > 3:
                col_val = 0
                row_val += 1

        clear_button = tk.Button(root, text="Clear", padx=30
        , pady=25
        , command=self.clear)
        clear_button.grid(row=row_val, column=col_val, columnspan=2)

        self.history = []  # Initialize an empty list for history log
        
        root.resizable(True, True)

        # Configure row and column weights for resizing
        for i in range(1, 6):  # Assuming you have a maximum of 5 rows
            root.grid_rowconfigure(i, weight=1)
        for i in range(4):  # Assuming you have 4 columns
            root.grid_columnconfigure(i, weight=1)

    def button_click(self, value):
        current = self.entry.get()
        self.entry.delete(0, tk.END)
        self.entry.insert(0, current + str(value))

    def clear(self):
        self.entry.delete(0, tk.END)

    def calculate(self):
        current = self.entry.get()
        try:
            result = eval(current)
            self.history.append(current + ' = ' + str(result))  # Add calculation to history log
            self.entry.delete(0, tk.END)
            self.entry.insert(0, result)
        except:
            self.entry.delete(0, tk.END)
            self.entry.insert(0, "Error")

    def trig_log_function(self, function):
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
            self.history.append(function + '(' + current + ') = ' + str(result))  # Add calculation to history log
            self.entry.delete(0, tk.END)
            self.entry.insert(0, result)
        except:
            self.entry.delete(0, tk.END)
            self.entry.insert(0, "Error")
            
    def print_to_file(self):
        with open('calculator_history.txt', 'w') as f:
            for i in self.history:
                f.write("%s\n" % i)
                
    def open_new_window(self):
        new_window = tk.Toplevel(self.root)
        new_window.title("History Log")
        log_text = tk.Text(new_window, height=20, width=40)
        log_text.pack()
        log_text.insert(tk.END, "\n".join(self.history))
        print = tk.Button(new_window, text='Print to File', padx=5, pady=5, command=self.print_to_file)
        print.pack()
        

if __name__ == "__main__":
    root = tk.Tk()
    app = Calculator(root)
    root.mainloop()
