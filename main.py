import argparse
import ast
import csv
import os
import sys
from pathlib import Path


class Task:
    def __init__(self, title, priority='Medium', done=False):
        self.title = title
        self.priority = priority
        self.done = done


class TodoList:
    def __init__(self):
        self.file_name = 'todo.csv'
        self.tasks = []
        self.load_tasks()

    def load_tasks(self):
        # Check if the file exists already or not
        if not Path(self.file_name).is_file():
            Path(self.file_name).touch()
            # handle platform
            if os.name == 'nt':  # For Windows
                os.system(f'attrib +h {self.file_name}')
            else:  # For Unix-based systems (Linux, macOS)
                hidden_file_name = f'.{self.file_name}'
                os.rename(self.file_name, hidden_file_name)
                self.file_name = hidden_file_name
        else:
            # Open the CSV file
            with open(self.file_name, mode='r') as file:
                # Create a CSV reader object
                csv_reader = csv.reader(file)

                # Iterate over each row in the CSV file
                for row in csv_reader:
                    self.create_task(row[0], row[1], True if row[2] == "True" else False)

    def save_tasks(self):
        # Open the file in write mode
        with open(self.file_name, 'w', newline='') as file:
            writer = csv.writer(file)
            # Write each row
            for task in self.tasks:
                writer.writerow([task.title, task.priority, task.done])

    def create_task(self, title, priority='Medium', done=False):
        task = Task(title, priority, done)
        self.tasks.append(task)
        self.save_tasks()

    def list_tasks(self, args=None):
        if len(self.tasks) == 0:
            print("No tasks found.")
        else:
            print("Task List:")
            print("{:<6} {:<15} {:<10} {:<10}".format('Index', 'Title', 'Priority', 'done'))
            for index, task in enumerate(self.tasks):
                print("{:<6} {:<15} {:<10} {:<10}".format(index + 1, task.title, task.priority, 1 if task.done else 0))

    def update_task(self, title, field, edit):
        for task in self.tasks:
            if task.title == title:
                match field.lower():
                    case 'priority':
                        task.priority = edit
                    case 'done':
                        task.done = True if edit == '1' else False
                    case _:
                        print(f"field \"{field}\" is not a valid field")
                break
        else:
            print("Invalid title.")
        self.save_tasks()

    def delete_task(self, title):
        for task in self.tasks:
            if task.title == title:
                self.tasks.remove(task)
                self.save_tasks()
                return True
        return False

    def clear_list(self):
        if len(self.tasks) == 0:
            return False
        else:
            self.tasks.clear()
            self.save_tasks()
            return True

    def get_task(self, title):
        for task in self.tasks:
            if task.title == title:
                return task
        else:
            return False


def create_task(todo_list, name, priority, done):
    todo_list.create_task(name, priority, done)
    print(f"Task {name} created successfully.")


def update_task(todo_list, title, field, edit):
    todo_list.update_task(title, field, edit)


def delete_task(todo_list, title):
    if todo_list.delete_task(title):
        print(f"Task \"{title}\" deleted successfully.")
    else:
        print("Invalid title.")


def clear_tasks(todo_list):
    if todo_list.clear_list():
        print("To-do list cleared")
    else:
        print("To-do list is already empty")


def search_task(todo_list, title):
    task = todo_list.get_task(title)
    if task:
        print("{:<15} {:<10} {:<10}".format("Title", "Priority", "Done"))
        print("{:<15} {:<10} {:<10}".format(task.title, task.priority, task.done))
    else:
        print(f"Task \"{title}\" not found!")


def main():
    todo_list = TodoList()
    parser = argparse.ArgumentParser(description="Task management script")
    subparsers = parser.add_subparsers(dest='command', help='Sub-command help')

    # Sub-parser for the "list" command
    parser_list = subparsers.add_parser('list', help='List all tasks')
    parser_list.set_defaults(func=todo_list.list_tasks)

    # Sub-parser for the "create_task" command
    parser_create = subparsers.add_parser('create', help='Create a new task')
    parser_create.add_argument('name', type=str, help='Name of the task')
    parser_create.add_argument('priority', type=str, nargs='?', default='Medium',
                               help='Priority of the task (default: Medium)')
    parser_create.add_argument('done', type=str, nargs='?', default='0',
                               help='Description of the task situation 1 or 0 (default: 0)')
    parser_create.set_defaults(
        func=lambda arguments: create_task(todo_list, arguments.name, arguments.priority,
                                           False if arguments.done == '0' else True))

    # sub-parser for the "update" command
    parser_list = subparsers.add_parser('update', help='update a task')
    parser_list.add_argument('title', help='the title of the task')
    parser_list.add_argument('field', help='the field you want to update')
    parser_list.add_argument('edit', help='the new value')
    parser_list.set_defaults(func=lambda arguments: update_task(todo_list, arguments.title, arguments.field,
                                                                arguments.edit))

    # sub-parser for the "delete" command
    parser_list = subparsers.add_parser('delete', help='delete a task from list')
    parser_list.add_argument('title', help='the title of the task you want to delete')
    parser_list.set_defaults(func=lambda arguments: delete_task(todo_list, arguments.title))

    # sub-parser for the "clear" command
    parser_list = subparsers.add_parser('clear', help='clear all the tasks in list')
    parser_list.set_defaults(func=lambda arguments: clear_tasks(todo_list))

    # sub-parser for the "search" command
    parser_list = subparsers.add_parser('search', help='get information about a task')
    parser_list.add_argument('title', help='the title of the task you want to search')
    parser_list.set_defaults(func=lambda arguments: search_task(todo_list, arguments.title))

    args = parser.parse_args()
    if args.command:
        args.func(args)
    else:
        parser.print_help()


if __name__ == "__main__":
    main()
