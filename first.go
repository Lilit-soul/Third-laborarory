package main

import (
	"fmt"
	"math"
)

func main() {
	x_start := -5.0
	x_end := 5.0
	dx := 0.2

	fmt.Println("  [-5;-2]: y = (1/3)*(x+2)")
	fmt.Println("  [-2; 2]: y = tg(x/2)")
	fmt.Println("  [ 2; 5]: y = 0.5x - 1.5")
	fmt.Println()

	fmt.Println("   x    |       y       | Отрезок")
	fmt.Println("--------------------------------")

	for x := x_start; x <= x_end+1e-9; x += dx {
		var y float64
		var segment string

		if x <= -2.0 {
			y = (1.0/3.0) * (x + 2.0)
			segment = "[-5; -2]"
		} else if x < 2.0 {
			y = math.Tan(x / 2.0)
			segment = "[-2; 2]"
		} else {
			y = 0.5*x - 1.5
			segment = "[2; 5]"
		}

		fmt.Printf("%6.1f  %15.6f   %s\n", x, y, segment)
	}
    fmt.Println()
    fmt.Println("Примечание: в точках x = -2 и x = 2 - разрывы функции")
}
