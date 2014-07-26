from pylab import *

t = loadtxt("data.dat")

x = t[:,2].reshape(280, 50)
y = t[:,3].reshape(280, 50)
u = t[:,5].reshape(280, 50)
v = t[:,6].reshape(280, 50)
rho = t[:,4].reshape(280, 50)
p = t[:,7].reshape(280, 50)
title("u")
contourf(x, y, u, 10)
colorbar()
figure()
title("M")
contourf(x, y, sqrt(v*v + u*u)/sqrt(1.4*p/rho), 10)
colorbar()
figure()
contourf(x, y, rho, 10)
colorbar()

figure()
contourf(x, y, p, 10)
colorbar()

figure()
plot(x[:,5], u[:,5])
plot(x[:,5], p[:,5])
plot(x[:,5], rho[:,5])
plot(x[:,5], v[:,5])

show()
