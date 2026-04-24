package main

import "fmt"

func gcd(a, b int64) int64 {
    for b != 0 {
        a, b = b, a%b
    }
    return a
}

func powInt64(base int64, exp int) int64 {
    result := int64(1)
    for i := 0; i < exp; i++ {
        result *= base
    }
    return result
}

// Рекурсивное вычисление числа Эйлера
func eulerianNumber(n, k int) int64 {
    if n == 0 && k == 0 {
        return 1
    }
    if k < 0 || k >= n {
        return 0
    }
    return int64(n-k)*eulerianNumber(n-1, k-1) + int64(k+1)*eulerianNumber(n-1, k)
}

func main() {
    var a, b int
    fmt.Print("Введите а и b: ")
    fmt.Scan(&a, &b)

    if a > 10 || a < 1 || b < 1 || b > 10{
        fmt.Println("Числа должны быть от 1 до 10")
        return
    }

    if b == 1 {
        fmt.Println("infinity")
        return
    }

    var numerator int64 = 0
    for k := 0; k < a; k++ {
        numerator += eulerianNumber(a, k) * powInt64(int64(b), a-k)
    }

    denominator := powInt64(int64(b-1), a+1)

    g := gcd(numerator, denominator)
    fmt.Printf("%d/%d\n", numerator/g, denominator/g)
}
