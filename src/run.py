from api import speed

if __name__ == "__main__":
    ni = 281
    nj = 51
    
    fsmach = 0.8
    alpha = 0.0
    
    tol = 1e-8
    iread = True
    # integrator 0=euler, 1=jst, 2=rk2(tvd)
    integrator = 2
    
    speed(ni, nj, fsmach, alpha, tol, iread, integrator);
