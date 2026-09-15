function comparar_metodos_control_motor()
    % Parámetros comunes
    T = 90; N = 50; dt = T/N;
    x0 = [0; 0]; xf = [pi/2; 0];
    
    % Matrices del LQR
    Q = eye(2); R = 1; A = [0 1; 0 0]; B = [0; 1];
    K = lqr(A, B, Q, R);

    % Control con retroalimentación
    u_opt = -K * (x0 - xf);
    [x1, x2] = simular_dinamica(u_opt, x0, dt)
    
    % Graficar resultados
    subplot(2,1,1)
    plot(x1, 'b-', 'LineWidth', 2); ylabel('Posición (rad)');
    title('Control LQR');
    subplot(2,1,2)
    plot(x2, 'r-', 'LineWidth', 2); ylabel('Velocidad (rad/s)');
end

function [x1, x2] = simular_dinamica(u, x0, dt)
    N = length(u);
    x = zeros(2, N+1);
    x(:,1) = x0;
    for k = 1:N
        % Dinámica simple: x1' = x2, x2' = u
        x(1,k+1) = x(1,k) + dt * x(2,k);
        x(2,k+1) = x(2,k) + dt * u(k);
    end
    x1 = x(1,:);
    x2 = x(2,:);
end
