#include <unity.h>

void setUp(void)
{
}

void tearDown(void)
{
}

//* https://www.geeksforgeeks.org/lagranges-interpolation/

// To represent a data point corresponding to x and y = f(x)
struct Point
{
    double x, y;
};

// function to interpolate the given data points using Lagrange's formula
// xi corresponds to the new data point whose value is to be obtained
// n represents the number of known data points
double interpolate(Point f[], int n, double xi)
{
    double result = 0; // Initialize result
    for (int i = 0; i < n; i++)
    {
        // Compute individual terms of above formula
        double term = f[i].y;
        for (int j = 0; j < n; j++)
        {
            if (j != i)
                term = term * (xi - f[j].x) / (f[i].x - f[j].x);
        }
        // Add current term to result
        result += term;
    }
    return result;
}

// Za xi == f[i].x -> f[i].y,
// inace se vraca tacka na pravoj liniji izmedju 2 sidra koja odgovara xi
double interpolate_simple(Point f[], int n, double xi)
{
    if (xi < f[0].x)
        return 999;
    for (size_t i = 0; i < n; i++)
    {
        if (xi == f[i].x)
            return f[i].y;
        if (xi < f[i + 1].x)
        {
            double dx = xi - f[i].x;
            double Dx = f[i + 1].x - f[i].x;
            double Dy = f[i + 1].y - f[i].y;
            double dy = dx * Dy / Dx;
            return f[i].y + dy;
        }
    }
    return 0;
}

//TODO https://www.geeksforgeeks.org/newtons-divided-difference-interpolation-formula/?ref=rp

Point arr[] = {
    {0.2989, 105},
    {0.398, 95},
    {0.5386, 85},
    {0.7415, 75},
    {1.04, 65},
    {1.4881, 55},
    {2.1757, 45},
    {3.2564, 35},
    {5.0, 25},
    {7.8943, 15},
    {12.8515, 5},
};

int array_len() { return sizeof(arr) / sizeof(Point); }

void test_assert_equal_double(double expected, double actual, double precision = 1.0)
{
    TEST_ASSERT_TRUE_MESSAGE(actual >= expected - precision, "vrednost je ispod donje granice");
    TEST_ASSERT_TRUE_MESSAGE(actual <= expected + precision, "vrednost je iznad gornje granice");
}

void interpolate_simple_test()
{
    double y;
    y = interpolate_simple(arr, array_len(), 0.1);
    TEST_ASSERT_EQUAL(999, y);
    y = interpolate_simple(arr, array_len(), 100);
    TEST_ASSERT_EQUAL(0, y);

    y = interpolate_simple(arr, array_len(), 5.0);
    TEST_ASSERT_EQUAL(25, y);
    y = interpolate_simple(arr, array_len(), 1.04);
    TEST_ASSERT_EQUAL(65, y);

    y = interpolate_simple(arr, array_len(), 8);
    test_assert_equal_double(14, y);
    y = interpolate_simple(arr, array_len(), 1);
    test_assert_equal_double(67, y);
}

void test_interpolate_anchors()
{
    double y;
    y = interpolate(arr, array_len(), 5.5);
    TEST_ASSERT_EQUAL(22, y);
    test_assert_equal_double(22.5, y);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    // RUN_TEST(test_interpolate_anchors);
    RUN_TEST(interpolate_simple_test);
    UNITY_END();
}