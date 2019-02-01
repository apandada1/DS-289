function demoOscRK1(tf, nsteps)
    tstep = tf / nsteps;
    t = linspace(0, tf, nsteps + 1);

    xRK = zeros(size(t));
    u = [1.0; 0.0];
    xRK(1) = u(1);
    for k=1:nsteps
        uNext = stepRK1_np(tstep, t(k), u, 'fnOsc');
        u = uNext;
        xRK(k+1) = u(1);
    end

    xExact = cos(t);
    figure(1);
    plot(t, xRK, '-g;Euler Forward;', t, xExact, '-k;Exact;');
    grid on;
    figure(2);
    plot(t, xExact - xRK, '-r;Error;');
    grid on;
