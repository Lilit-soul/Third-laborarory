package main

import (
	"fmt"
	"math"
)

func main() {
	var n, m int
	fmt.Print("Введите n и m: ")
	fmt.Scan(&n, &m)

	a := make([]int64, n)
	fmt.Print("Введите числа: ")
	for i := 0; i < n; i++ {
		fmt.Scan(&a[i])
	}

	// Префиксные суммы
	prefix := make([]int64, n+1)
	for i := 0; i < n; i++ {
		prefix[i+1] = prefix[i] + a[i]
	}

	// dp[i][last] - максимальная разница (текущий игрок - противник)
	dp := make([][]int64, n+1)
	for i := range dp {
		dp[i] = make([]int64, m+1)
		for j := range dp[i] {
			dp[i][j] = math.MinInt64
		}
	}

	// База: чисел нет
	for last := 0; last <= m; last++ {
		dp[n][last] = 0
	}

	// Заполняем dp от конца к началу
	for i := n - 1; i >= 0; i-- {
		for last := 0; last <= m; last++ {
			best := int64(math.MinInt64)

			// Перебираем, сколько взять
			for k := 1; k <= m && i+k <= n; k++ {
				if k == last {
					continue
				}

				sum := prefix[i+k] - prefix[i]
				diff := dp[i+k][k] - sum

				if diff > best {
					best = diff
				}
			}

			if best != math.MinInt64 {
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
