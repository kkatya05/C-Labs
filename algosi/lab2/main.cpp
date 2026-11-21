#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

struct Point
{
    double x;
    double y;
};

double distance(Point a, Point b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

int main()
{
    int n;
    std::cout << "Enter number of points (1-18): ";
    if (!(std::cin >> n) || n < 1 || n > 18)
    {
        std::cout << "Invalid size" << std::endl;
        return 1;
    }

    std::vector<Point> points(n);
    std::cout << "Enter X and Y for each point: " << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cin >> points[i].x >> points[i].y;
    }

    if (n == 1)
    {
        std::cout << "Route: 1 -> 1\nLength: 0.000" << std::endl;
        return 0;
    }

    int m = n - 1;
    int states = 1 << m;
    const double INF = 1e100;

    // Бит j обозначает посещение точки j + 2 (первая точка всегда старт).
    // dp[mask * m + j] — длина пути до точки j + 2 через точки mask.
    std::vector<double> dp(states * m, INF);
    std::vector<double> dist(n * n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            dist[i * n + j] = distance(points[i], points[j]);
        }
    }

    for (int j = 0; j < m; j++)
    {
        dp[(1 << j) * m + j] = dist[j + 1];
    }

    for (int mask = 1; mask < states; mask++)
    {
        for (int j = 0; j < m; j++)
        {
            if ((mask & (1 << j)) == 0)
                continue;
            int prevMask = mask ^ (1 << j);
            if (prevMask == 0)
                continue;

            for (int k = 0; k < m; k++)
            {
                if ((prevMask & (1 << k)) != 0)
                {
                    double value = dp[prevMask * m + k] + dist[(k + 1) * n + j + 1];
                    if (value < dp[mask * m + j])
                        dp[mask * m + j] = value;
                }
            }
        }
    }

    int mask = states - 1;
    int last = 0;
    double best = INF;
    for (int j = 0; j < m; j++)
    {
        double value = dp[mask * m + j] + dist[(j + 1) * n];
        if (value < best)
        {
            best = value;
            last = j;
        }
    }

    // Восстанавливаем маршрут по dp, не храня отдельную таблицу предков.
    std::vector<int> route(n + 1, 0);
    for (int pos = n - 1; pos >= 1; pos--)
    {
        route[pos] = last + 1;
        int prevMask = mask ^ (1 << last);
        if (prevMask == 0)
            break;
        double minValue = INF;
        int prev = 0;
        for (int k = 0; k < m; k++)
        {
            if ((prevMask & (1 << k)) != 0)
            {
                double value = dp[prevMask * m + k] + dist[(k + 1) * n + last + 1];
                if (value < minValue)
                {
                    minValue = value;
                    prev = k;
                }
            }
        }
        mask = prevMask;
        last = prev;
    }

    std::cout << "Route: ";
    for (int i = 0; i <= n; i++)
    {
        if (i > 0)
            std::cout << " -> ";
        std::cout << route[i] + 1;
    }
    std::cout << "\nLength: " << std::fixed << std::setprecision(3) << best << std::endl;
    return 0;
}

// g++ main.cpp -o main.exe -std=c++11
// .\main.exe
