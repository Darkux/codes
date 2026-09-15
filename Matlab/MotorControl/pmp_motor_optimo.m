function pmp_motor_optimo()
    % Tiempo de simulación
    T = 10; % Tiempo total de simulación
    tspan = [0 T]; % Rango de tiempo para la solución

    % Condiciones iniciales: [x1; x2; p1; p2]
    p1_guess = 90; % Valor inicial de p1
    p2_guess = 0; % Valor inicial de p2
    y0 = [0; 0; p1_guess; p2_guess]; % Condición inicial para los estados y coestados

    % Resolver el sistema usando ode45
    [t, y] = ode45(@ecuaciones_pmp, tspan, y0);

    % Extraer las variables del resultado
    x1 = y(:,1); % Posición
    x2 = y(:,2); % Velocidad
    p2 = y(:,4); % Coestado p2
    u = -p2 / 2; % Control óptimo

    % Graficar resultados
    figure;
    subplot(3,1,1); plot(t, x1, 'b', 'LineWidth', 2); ylabel('Posición (x1) [rad]');
    title('Control Óptimo - Posición del Motor');
    subplot(3,1,2); plot(t, x2, 'r', 'LineWidth', 2); ylabel('Velocidad (x2) [rad/s]');
    title('Velocidad del Motor');
    subplot(3,1,3); plot(t, u, 'k', 'LineWidth', 2); ylabel('Control (u) [Nm]'); xlabel('Tiempo [s]');
    title('Control Óptimo Aplicado');
end

function dydt = ecuaciones_pmp(~, y)
    x1 = y(1); % Posición
    x2 = y(2); % Velocidad
    p1 = y(3); % Coestado p1
    p2 = y(4); % Coestado p2

    % Control óptimo según el Principio del Máximo de Pontryagin
    u = p2 / 2;

    % Ecuaciones del sistema
    dx1 = x2;
    dx2 = u;

    % Ecuaciones del coestado
    dp1 = 0; % Coestado p1 no cambia
    dp2 = p1; % Ecuación de coestado para p2

    dydt = [dx1; dx2; dp1; dp2];
end
