import time

def calculate(x: float) -> float:
    return x**2 - x**2 + x**4 - x**5 + x + x


def main():
    x = 1.5  
    
    while True:
        try:
            p = int(input("\nNumber of iterations : "))
                
        except ValueError:
            # Если введено не число — завершаем программу
            print("Error: not a number! ")
            break
        
        start_time = time.perf_counter()
        
        for _ in range(p):
            result = calculate(x)
        
        end_time = time.perf_counter()
        
        duration_us = (end_time - start_time) * 1_000_000
        
        print(f" Time: {duration_us:.2f} microseconds")
        print("-" * 50)


if __name__ == "__main__":
    main()