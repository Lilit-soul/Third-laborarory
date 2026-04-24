package main

import (
	"fmt"
)

func main() {
	var n, m, variant int
    fmt.Print("Введите n, m и вариант доп условия: ")
	fmt.Scan(&n, &m, &variant)
    
    if n<5 {
        fmt.Println("Число n слишком маленькое!")
        return
    }
    
    fmt.Print("Введите ", n, " чисел: ")
	a := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&a[i])
	}

	// Префиксные суммы
	prefix := make([]int, n+1)
	for i := 0; i < n; i++ {
		prefix[i+1] = prefix[i] + a[i]
	}

	// dp[i][last] - максимальная разница (текущий игрок - противник)
	// last - сколько чисел взял предыдущий игрок
	dp := make([][]int, n+1)
	for i := range dp {
		dp[i] = make([]int, m+1)
		for j := range dp[i] {
			dp[i][j] = -1 << 60
		}
	}

	// База: чисел нет, разница = 0
	for last := 0; last <= m; last++ {
		dp[n][last] = 0
	}

	// Заполняем dp от конца к началу
	for i := n - 1; i >= 0; i-- {
		for last := 0; last <= m; last++ {
			best := -1 << 60

			// Перебираем, сколько чисел взять (от 1 до m)
			for k := 1; k <= m && i+k <= n; k++ {
				// Проверка ограничения в зависимости от варианта
				if variant == 1 {
					// Вариант 1: нельзя повторять СВОЙ прошлый ход
					if k == last {
						continue
					}
				} else {
					// Вариант 2: нельзя повторять ход ПРОТИВНИКА
					if k == last {
						continue
					}
				}

				sum := prefix[i+k] - prefix[i]
				val := sum - dp[i+k][k]
				if val > best {
					best = val
				}
			}

			if best != -1<<60 {
				dp[i][last] = best
			}
		}
	}

	// Вывод результата
	if dp[0][0] > 0 {
		fmt.Println("1")
	} else {
		fmt.Println("0")
	}
}
