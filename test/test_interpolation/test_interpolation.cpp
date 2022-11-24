#include <unity.h>

void setUp(void)
{
}

void tearDown(void)
{
}

//* https://www.geeksforgeeks.org/lagranges-interpolation/

// To represent a data point corresponding to x and y = f(x)
struct Data
{
    int x, y;
};

// function to interpolate the given data points using Lagrange's formula
// xi corresponds to the new data point whose value is to be obtained
// n represents the number of known data points
double interpolate(Data f[], int xi, int n)
{
    double result = 0; // Initialize result
    for (int i = 0; i < n; i++)
    {
        // Compute individual terms of above formula
        double term = f[i].y;
        for (int j = 0; j < n; j++)
        {
            if (j != i)
                term = term * (xi - f[j].x) / double(f[i].x - f[j].x);
        }
        // Add current term to result
        result += term;
    }
    return result;
}

void test_init()
{
    int x = 3;
    TEST_ASSERT_EQUAL(3, x);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_init);
    UNITY_END();
}