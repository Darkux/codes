function pos = Novit(~)
%#codegen
persistent t initialized lastPos

% Rango físico esperado desde el Novint Falcon (ajustar según tu setup)
r = 0.04;  % metros → [-0.04, 0.04] → mapeado a [-1, 1]

if isempty(initialized)
    % Crear servidor TCP en puerto 25000
    t = tcpip('0.0.0.0', 25000, 'NetworkRole', 'server');
    
    % Configuraciones importantes
    set(t, 'InputBufferSize', 1024);   % tamaño de buffer
    set(t, 'Timeout', 2);              % evita bloqueos eternos
    set(t, 'Terminator', 'LF');        % esperar salto de línea '\n'

    fopen(t);                          % abrir conexión (bloquea hasta que un cliente se conecte)

    lastPos = [0, 0, 0];
    initialized = true;
end

if t.BytesAvailable > 0
    % Leer datos como string hasta el terminador
    data = fscanf(t, '%s');  % bloquea hasta '\n' o timeout

    % Parsear valores separados por coma
    valores = sscanf(data, '%f,%f,%f');

    if numel(valores) == 3
        % Normalizar al rango [-1, 1] con saturación
        valoresNorm = max(-1, min(1, valores(:)' / r));
        lastPos = valoresNorm;
    end
end

pos = lastPos;
end
