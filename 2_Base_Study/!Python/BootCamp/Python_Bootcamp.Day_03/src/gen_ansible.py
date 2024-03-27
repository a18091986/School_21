from pathlib import Path
import yaml  


def get_info_from_todo(file_path: str): 
    with open(file_path, 'r') as f:
        return yaml.safe_load(f)


def install_packages(install_packages: list):
    return [
        {
            "name": "Install packages",
            "ansible.builtin.apt":
            {
                "package": install_packages
            }
        }
    ]

def make_dir(path: Path):
    return [
        {
            "name": "Make Directory",
            "ansible.builtin.file":
            {
                "path": path,
                "state": "directory",
                "mode": "0777"
            }
        }
    ]


def copy_files(files: list, dest: str):
    return [
        {
            "name": "Copy file",
            "ansible.builtin.copy":
            {
                "src": _,
                "dest": dest,
                "mode": "0777"
            }
        }
        for _ in files
    ]


def run_consumer(script_path: str, bad_guys: list):
    return [
        {
            "name": "Run consumer",
            "ansible.builtin.script": f"{script_path}/consumer.py -e {','.join(bad_guys)}",
            "args":
            {
                "executable": "python3"
            }
            
        }
    ]


def save_data(yaml_data, file_src):
    with open(file_src, 'w') as f:
        yaml.dump(yaml_data, f, Dumper=yaml.Dumper, sort_keys=False)


if __name__ == "__main__":

    temp_path = str(Path(Path.cwd(), '..', 'tmp'))
    
    y_data = get_info_from_todo("../materials/todo.yml")
    print(y_data.get('server'))
    playbook = [{'name': 'Playbook', 'hosts': 'localhost', 'tasks':[]}]
    playbook[0]['tasks'].extend(install_packages(y_data["server"]["install_packages"]))
    playbook[0]['tasks'].extend(make_dir(temp_path))
    playbook[0]['tasks'].extend(copy_files(y_data["server"]["exploit_files"], temp_path))
    playbook[0]['tasks'].extend(run_consumer(temp_path, y_data["bad_guys"]))
    

    save_data(playbook, "deploy.yml")