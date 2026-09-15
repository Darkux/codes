function [t,x1, x2,x3] = control_motor_optimo()
    % Parámetros
    T = 10;           % Tiempo total (segundos)
    N = 50;          % Número de pasos
    dt = T/N;        % Paso de tiempo
    x0 = [0; 0];     % Posición y velocidad inicial
    xf = [90; 0];     % Posición y velocidad final

    % Valor inicial para u
    u0 = zeros(N,1);

    % Optimización
    options = optimoptions('fmincon', 'Display','iter','Algorithm','sqp');
    u_opt = fmincon(@(u) costo(u, dt), u0, [],[],[],[], -5*ones(N,1), 5*ones(N,1), ...
                    @(u) restricciones(u, x0, xf, dt), options);

    % Simulación del sistema con u óptimo
    [x1, x2] = simular_dinamica(u_opt, x0, dt);
    x3 = u_opt';
    % Graficar resultados
    t = linspace(0, T, N+1);

    figure;
    subplot(3,1,1)
    plot(t, x1, 'b-', 'LineWidth', 2); ylabel('Posición (rad)');
    subplot(3,1,2)
    plot(t, x2, 'r-', 'LineWidth', 2); ylabel('Velocidad (rad/s)');
    subplot(3,1,3)
    plot(t(1:N), u_opt, 'k-', 'LineWidth', 2); ylabel('Control u'); xlabel('Tiempo (s)');
end

function J = costo(u, dt)
    % Costo cuadrático del esfuerzo de control
    J = sum(u.^2) * dt;
end

function [c, ceq] = restricciones(u, x0, xf, dt)
    % Simula la dinámica y evalúa la condición final
    [x1, x2] = simular_dinamica(u, x0, dt);
    x_final = [x1(end); x2(end)];
    ceq = x_final - xf;  % Queremos que x(T) = xf
    c = [];              % No hay restricciones de desigualdad
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
