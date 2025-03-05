from sympy import symbols, integrate, atan, pi

# Define variables
x, y = symbols('x y')

# Define the integrand
integrand = ((x**2 + y**2) * (pi/2 - 2 * atan(y / x))) / 2
right = integrate(integrate(integrand, (y, 0, 2 - x)), (x, 1, 2))
print(right.simplify())

integrand = ((x**2 + y**2) * (pi/2 - 2 * atan(y / x))) / 2
left = integrate(integrate(integrand, (y, 0, x)), (x, 0, 1))
print(left.simplify())

integrand = 2 * (y+1)
tri = integrate(integrate(integrand, (y, -1, x)), (x, -1, 0))
print(tri.simplify())

print((left.simplify() + right.simplify() + tri.simplify()) / 2)
