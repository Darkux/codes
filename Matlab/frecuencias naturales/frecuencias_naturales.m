clear all;
GA = []
% Configura el puerto serial
serialObj = serialport("COM17", 115200);  % Ajusta según tu puerto

% Parámetros
fs = 200;              % Frecuencia de muestreo (Hz)
N = 64;               % Muestras por bloque de FFT
T_total = 10;          % Duración total (segundos)
totalSamples = fs * T_total;

dataBuffer = zeros(N, 1);
rawSignal = zeros(totalSamples, 1);  % Para la señal cruda
dominantFreqs = zeros(floor(totalSamples/N), 1);

% Configura figura del espectro en tiempo real
figure;
hPlot = plot(nan, nan);
xlabel('Frecuencia (Hz)');
ylabel('Amplitud');
title('Espectro en Tiempo Real');
grid on;
xlim([0 fs/2]);
ylim([0 .3]);

% Bucle de adquisición
idxGlobal = 1;
for cycle = 1:floor(totalSamples / N)
    for i = 1:N
        line = readline(serialObj);
        value = str2double(line);
        if isnan(value)
            value = 0;
        end
        accel_g = (value / 16384.0) - 1.0;
        dataBuffer(i) = accel_g;
        rawSignal(idxGlobal) = accel_g;
        idxGlobal = idxGlobal + 1;
    end

    % FFT
    Y = fft(dataBuffer);
    P2 = abs(Y / N);
    P1 = P2(1:N/2+1);
    P1(2:end-1) = 2 * P1(2:end-1);
    f = fs * (0:(N/2)) / N;

    % Actualizar gráfica de espectro
    set(hPlot, 'XData', f, 'YData', P1);
    drawnow;

    % Guardar frecuencia dominante
    [x, idx] = max(P1);
    dominantFreqs(cycle) = f(idx);
    fprintf('Frecuencia dominante: %.2f Hz\n', dominantFreqs(cycle));
    fprintf('Frecuencia Amplitud: %.2f Hz\n', x);
    GA = [GA,x];
end

disp("⏱️ Análisis terminado (10 segundos).");

% === Gráfica de evolución de frecuencias naturales ===
t_freq = (0:length(dominantFreqs)-1) * (N/fs);
figure;
plot(t_freq, dominantFreqs, 'b.-');
xlabel('Tiempo (s)');
ylabel('Frecuencia Dominante (Hz)');
title('Frecuencia Natural a lo largo del tiempo');
grid on;

% === Gráfica de señal cruda vs tiempo ===
t_raw = (0:totalSamples-1) / fs;
figure;
plot(t_raw, rawSignal, 'k');
xlabel('Tiempo (s)');
ylabel('Aceleración Z (g)');
title('Señal Aceleración Z vs Tiempo');
grid on;
