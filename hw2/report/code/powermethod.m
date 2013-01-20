
funciton lambda =Powermethod(A)
    [n,n] = size(A);       % number of rows and columns in A
    x = ones(n,1);         % creates a starting n-vector of all ones
    for i = 1:1000         
        x = x / norm2(x);  % norm2(x) is sqrt(x(1)^2 + x(2)^2 + ... + x(n)^2)
        x = A * x;         % use your parallel matrix * vector routine here
    end;
    lambda = norm2(x);
