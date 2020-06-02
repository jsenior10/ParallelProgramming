#pragma once
#include <functional>
#include <math.h>
#include <vector>

typedef std::function<float(const float)> unaryFunction;
typedef std::function<float(const float, const float)> binaryFunction;

inline std::vector<unaryFunction> initUnaryFunctions()
{
	std::vector<unaryFunction> result{
      sinf, cosf, expf,
      asinf, acosf, atanf,
      logf,
      sinhf, coshf, tanhf,
      fabsf,
      erff,

    };
    result.push_back([](float x) { return -x; });
    result.push_back([](float x) { return x * x; });
    result.push_back([](float x) { return x * x * x; });
    return result;
}

inline std::vector<std::function<float(const float, const float)>> initBinaryFunctions()
{
	std::vector<binaryFunction> result;
    result.push_back(fdimf);
    result.push_back([](const float a, const float b) { return a + b; });
    result.push_back([](const float a, const float b) { return a - b; });
    result.push_back([](const float a, const float b) { return a * b; });

    //result.push_back([](float a, float b) { return a / b; });
    result.push_back([](const float a, const float b) { return sin(a * b); });
    //result.push_back([](float a, float b) { return cos(a*b); });
    result.push_back([](float a, float b) { return tan(a * b); });
    //result.push_back([](float a, float b) { return powf(a,b); });
    //result.push_back([](float a, float b) { return std::max(a,b); });
    //result.push_back([](float a, float b) { return std::min(a,b); });
    return result;
}

const std::vector<unaryFunction> unaryFunctions = initUnaryFunctions();
const std::vector<binaryFunction> binaryFunctions = initBinaryFunctions();

typedef std::function<void(const int*, const float*, float*)> unaryVectorFunction;
typedef std::function<void(const int*, const float*, const float*, float*)> binaryVectorFunction;

inline std::vector<unaryVectorFunction> initUnaryVectorFunctions()
{
	std::vector<unaryVectorFunction> result;
    result.push_back(vssin);
    result.push_back(vscos);
    result.push_back(vsexp);
    //result.push_back(vslog10);
    result.push_back(vssinh);
    result.push_back(vscosh);
    result.push_back(vstanh);
    result.push_back(vsabs);
    //result.push_back(vssqrt);
    //result.push_back(vstanh);
    return result;
}

inline std::vector<binaryVectorFunction> initBinaryVectorFunctions()
{
	std::vector<binaryVectorFunction> result;
    result.push_back(vsadd);
    result.push_back(vssub);
    result.push_back(vsmul);

    // this is what a compound function (in this case, sin(a*b) looks like)
    result.push_back([](const int* n, const float* a, const float* b, float* c)
        {
            float* temp = new float[*n];
            vsmul(n, a, b, temp);
            vssin(n, temp, c);
            delete[] temp;
        });

    return result;
}

const std::vector<unaryVectorFunction> unaryVectorFunctions = initUnaryVectorFunctions();
const std::vector<binaryVectorFunction> binaryVectorFunctions = initBinaryVectorFunctions();