function trayectoria_con_PD()
    % Obtener trayectoria de referencia
    [t_ref, pos_ref, vel_ref, acc_ref] = control_motor_optimo;
    acc_ref = [acc_ref,acc_ref(end)];
    % Parámetros del controlador
    Kp = 20;
    Kd = 10;

    % Estado inicial
    x0 = [0; 0];

    % Intervalo de simulación
    tspan = [t_ref(1), t_ref(end)];

    % Simulación con ode45
    [t, x] = ode45(@(t,x) seguimiento_PD(t, x, Kp, Kd, t_ref, pos_ref, vel_ref, acc_ref), tspan, x0);

    % Interpolar referencias para comparar en gráfico
    pos_r = interp1(t_ref, pos_ref, t);
    vel_r = interp1(t_ref, vel_ref, t);
    acc_r = interp1(t_ref, acc_ref, t);

    % Calcular u aplicado
    u_aplicado = acc_r - Kp*(x(:,1) - pos_r) - Kd*(x(:,2) - vel_r);

    % Graficar resultados
    figure;

    subplot(3,1,1)
    plot(t, x(:,1), 'b', 'LineWidth', 2); hold on;
    plot(t, pos_r, '--r'); ylabel('Posición');
    legend('Real','Referencia');

    subplot(3,1,2)
    plot(t, x(:,2), 'g', 'LineWidth', 2); hold on;
    plot(t, vel_r, '--r'); ylabel('Velocidad');
    legend('Real','Referencia');

    subplot(3,1,3)
    plot(t, u_aplicado, 'k', 'LineWidth', 2); hold on;
    plot(t, acc_r, '--r'); ylabel('Control u');
    xlabel('Tiempo (s)');
    legend('Aplicado','Referencia');

    sgtitle('Seguimiento de Trayectoria con Control PD + Feedforward');
end

function dx = seguimiento_PD(t, x, Kp, Kd, t_ref, pos_ref, vel_ref, acc_ref)
    % Interpolar referencias en el tiempo actual
    pos_r = interp1(t_ref, pos_ref, t);
    vel_r = interp1(t_ref, vel_ref, t);
    acc_r = interp1(t_ref, acc_ref, t);

    % Estados actuales
    x1 = x(1); % posición
    x2 = x(2); % velocidad

    % Control PD con término feedforward (aceleración deseada)
    u = acc_r - Kp*(x1 - pos_r) - Kd*(x2 - vel_r);

    % Dinámica
    dx = zeros(2,1);
    dx(1) = x2;
    dx(2) = u;
end
