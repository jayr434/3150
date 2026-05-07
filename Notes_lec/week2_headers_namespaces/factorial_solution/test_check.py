import subprocess

def run_program():
    result = subprocess.run(
        ["./check_program"], capture_output=True, text=True, check=True
    )
    return result.stdout.strip().splitlines()

def test_checkutils_and_mathextras():
    output = run_program()
    assert "5 is odd" in output[0]
    assert "6 is even" in output[1]
    assert "factorial(5) = 120" in output[2]
