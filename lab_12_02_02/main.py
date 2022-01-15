from arr import *
from tkinter import *
from tkinter import messagebox as mb

def show_fib_arr():
    try:
        n = int(entry_field.get())
        if n <= 0: 
            raise EXCEPTION("Неположительное число")
    except:
        mb.showerror(title='Ошибка ввода!', message='Ошибочка вышла...')
        return
    
    arr = arr_fill_with_fib(n)
    lb_res.configure(text=f"Результат: {arr}")

def show_first_occurrances_arr():
    try:
        arr = list(entry_field.get().split())
        print(arr)
        for i in range(len(arr)):
            arr[i] = int(arr[i])
    except:
        mb.showerror(title='Ошибка ввода!', message='Ошибочка вышла...')
        return
    
    arr_new = arr_move_first_occurrance(arr)
    lb_res.configure(text=f"Результат: {arr_new}")

def clear_entry_field():
    entry_field.delete(0, END)

def clear_result_field():
    lb_res['text'] = ""

def clear_all_fields():
    entry_field.delete(0, END)
    lb_res['text'] = ""

def info():
    mb.showinfo('Информация', '12 лабораторная работа по С.\n'
                              'Автор: Морозов Д.В., ИУ7-32Б')


window = Tk()
window.title("12 лабораторная работа по С")
window.geometry("300x445")

# Меню
menu = Menu()
clear_field = Menu(tearoff=0)
clear_field.add_command(label='Поле ввода', command=clear_entry_field)
clear_field.add_command(label='Поле вывода', command=clear_result_field)
clear_field.add_command(label='Все поля', command=clear_all_fields)

actions = Menu(tearoff=0)
actions.add_command(label='Заполнить массив числами Фибоначчи', command=show_fib_arr)
actions.add_command(label='Вывести первые вхождения элементов массива', command=show_first_occurrances_arr)

menu.add_cascade(label='Действия', menu=actions)
menu.add_cascade(label='Очистка полей', menu=clear_field)
menu.add_cascade(label='Информация', command=info)

window.config(menu=menu)

# Описание виджетов
entry_field = Entry(width=25, justify=RIGHT, font=("TimesNewRoman", 14))
b1 = Button(text='Массив Фибоначчи', bd=10, font=("TimesNewRoman", 14), command=lambda : show_fib_arr())
b2 = Button(text='Первые вхождения чисел', bd=10, font=("TimesNewRoman", 14), command=lambda : show_first_occurrances_arr())
lb_res = Label(window, text="Результат:", bg='gray', fg='white', font=("TimesNewRoman", 14))

# Расположение виджетов
entry_field.grid(row=0, column=0, columnspan=3, sticky='we', padx=5, pady=5)
b1.grid(row=1, column=1, columnspan=3, sticky='wens', padx=5, pady=5)
b2.grid(row=2, column=1, columnspan=3, sticky='wens', padx=5, pady=5)
lb_res.grid(row=3, column=0, columnspan=3, sticky='wens', padx=5, pady=5)

window.mainloop()







