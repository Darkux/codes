function motor_control_feedback()
    % Parámetros
    Kp = 10;    % Ganancia proporcional
    Kd = 5;     % Ganancia derivativa
    x_ref = [90,0,0];  % Posición deseada (por ejemplo, 1 radian o 1 metro)

    % Simular usando ODE45
    tspan = [0 5];           % tiempo de simulación (segundos)
    x0 = [0; 0];             % estado inicial: [posición; velocidad]
    [t, x] = ode45(@(t,x) motor_dynamics(t, x, Kp, Kd, x_ref), tspan, x0);

figure;

subplot(3,1,1);
plot(t, x(:,1), 'LineWidth', 2); hold on;
yline(x_ref(1), '--r', 'Posición deseada');
ylabel('Posición');

subplot(3,1,2);
plot(t, x(:,2), 'LineWidth', 2); hold on;
yline(x_ref(2), '--r', 'Velocidad deseada');
ylabel('Velocidad');

subplot(3,1,3);
acc = gradient(x(:,2), t);
plot(t, acc, 'LineWidth', 2); hold on;
yline(x_ref(3), '--r', 'control U');
xlabel('Tiempo (s)');
ylabel('control U');

sgtitle('Seguimiento de Posición, Velocidad y Aceleración');

end

function dx = motor_dynamics(~, x, Kp, Kd, x_ref)
    % Estados actuales
    x1 = x(1); % posición
    x2 = x(2); % velocidad
    
    % Referencias
    pos_ref = x_ref(1);
    vel_ref = x_ref(2);
    acc_ref = x_ref(3);

    % Control PD + A (aceleración deseada)
    u = acc_ref - Kp*(x1 - pos_ref) - Kd*(x2 - vel_ref);
    
    % Dinámica del sistema
    dx = zeros(2,1);
    dx(1) = x2;
    dx(2) = u;
end

