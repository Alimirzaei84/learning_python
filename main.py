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

    def list_tasks(self, args = None):
        if len(self.tasks) == 0:
            print("No tasks found.")
        else:
            print("Task List:")
            print("{:<6} {:<15} {:<10} {:<10}".format('Index', 'Title', 'Priority', 'done'))
            for index, task in enumerate(self.tasks):
                print("{:<6} {:<15} {:<10} {:<10}".format(index + 1, task.title, task.title, 1 if task.done else 0))


def create_task(todo_list, name, priority, done):
    todo_list.create_task(name, priority, done)
    print(f"Task {name} created successfully.")



def main():
    todo_list = TodoList()
    parser = argparse.ArgumentParser(description="Task management script")
    subparsers = parser.add_subparsers(dest='command', help='Sub-command help')

    # Sub-parser for the "list" command
    parser_list = subparsers.add_parser('list', help='List all tasks')
    parser_list.set_defaults(func=todo_list.list_tasks)  # Corrected line

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

    args = parser.parse_args()
    if args.command:
        args.func(args)
    else:
        parser.print_help()


if __name__ == "__main__":
    main()
