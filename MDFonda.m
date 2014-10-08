clear;

% Quantidade de valores de x, y e t que serão apanhados
disc_x =121;
disc_y = 121;
disc_t = 201;

% Intervalos de x, y e t
x_inicial = -3;
x_final = 3;
y_inicial = -3;
y_final = 3;
t_inicial = 0;
t_final = 1;

% Intervalo total de x, y e t
delta_x = x_final - x_inicial;
delta_y = y_final - y_inicial;
delta_t = t_final - t_inicial;

% Tamanho de cada intervalo na discretização
dx = delta_x / (disc_x - 1);
dy = delta_y / (disc_y - 1);
dt = delta_t / (disc_t - 1);

% Ponto de atuação da fonte
xs = 0;
ys = 0;

% Calculando x(i), um vetor com uma borta de dois zeros no inicio e no fim
for i = 1:disc_x + 4
    if (i <= 2 | i > disc_x + 2)
        x(i) = 0;
    else       
        x(i) = (i-3) * dx + x_inicial;
    end
end

% Calculando y(j), um vetor com uma borta de dois zeros no inicio e no fim
for j = 1:disc_y + 4
    if (j <= 2 | j > disc_y + 2)
        y(j) = 0;
    else
        y(j) = (j-3) * dy + y_inicial;
    end
end

% Período da onda
T = 0.1;
% Calculando t(k) e s(k)
for k = 1:disc_t
    t(k) = (k-1) * dt + t_inicial;
    termo_escroto = (pi*((2*t(k)/T)-1)).^2;
    s(k) = (1-2*(termo_escroto)) * exp(-1 * termo_escroto);
end

% Calculando F(x,y,t)
for i = 1: disc_x + 4
     for j = 1:disc_y + 4
         for k = 1:disc_t
             % Se for elemento da borda
             if (i <= 2 | i > disc_x + 2 | j <= 2 | j > disc_y + 2)
                 f(i,j,k) = 0;
             else
                % Se for fora da borda, mas for onde está a fonte
                if (x(i) == xs & y(j)== ys)
                     f(i,j,k) = s(k);
                % Se for fora da borda e longe da fonte
                else 
                     f(i,j,k) = 0;
                end
             end
         end
     end
end

% Calculando as matrizes a(i,j), b(i,j), c(x,y), d(i,j)
for i = 1:disc_x + 4
    for j = 1:disc_y + 4
        % Elementos da borda
        if (i <= 2 | i > disc_x + 2 | j <= 2 | j > disc_y + 2)
            c(i,j) = 0;
            a(i,j) = 0;
            b(i,j) = 0;
            d(i,j) = 0;
        % Elementos de fora da borda
        else
            c(i,j) = (x(i)+y(j))/4 +2;
            a(i,j) = (c(i,j) * dt/dx)^2;
            b(i,j) = (c(i,j) * dt/dy)^2;
            d(i,j) = ((c(i,j) * dt)^2) / (dx*dy);
        end
    end
end

% Calculando a matriz u(x,y,k)
for k = 1:disc_t
    for i = 1:disc_x + 4
        for j = 1:disc_y + 4
            % Se for elemento da borda ou matriz com k = 1 ou k = 2
            % (condições iniciais)
            if (i <= 2 | i > disc_x + 2 | j <= 2 | j > disc_y + 2 | k == 1 | k == 2)
                u(i, j, k) = 0;
            % Calcula u(x,y,k)
            else
                u(i, j, k) = -1/12 * (...
                                        a(i,j) * (...
                                            u(i-2,j,k-1) + u(i+2,j,k-1) - 16*(...
                                                u(i-1,j,k-1) + u(i+1,j,k-1)...
                                            ) + 30*u(i,j,k-1)...
                                        ) + ...
                                        b(i,j) * (...
                                            u(i,j-2,k-1) + u(i,j+2,k-1) - 16*(...
                                                u(i,j-1,k-1) + u(i,j+1,k-1)...
                                            ) + 30*u(i,j,k-1)...
                                        )...
                                    ) + ...
                                    2*u(i,j,k-1) - u(i,j,k-2) + d(i,j) * f(i,j,k-1);
            end
        end
    end
end

% Removendo as bordas de 0 criadas
xp(1:disc_x) = x(3:disc_x+2);
yp(1:disc_y) = y(3:disc_y+2);
% Remove as bordas da matriz U e pega uma amostra em um tempo detemrinado
ap(:,:) = u(3:disc_x+2,3:disc_y+2,    11  );
up(:,:,:) = u(3:disc_x+2,3:disc_y+2,:);
cp(:,:) = c(3:disc_x+2,3:disc_y+2);

% Plota a onda na tela
surf(xp,yp,ap, 'LineStyle', 'none', 'FaceColor', 'interp');
colormap hsv;
colorbar;
axis equal;


%menor_velocidade = min(min(c));
%maior_velocidade = max(max(c));


% Normalização (transforma os valores da matriz ap em valores de 0 a 1 e
% salva o maior e o menor valor

%menor = min(min(ap));
%maior = max(max(ap));

%ap = (ap - menor) ./ (maior - menor);
%zero_normalizado = -menor / (maior - menor);

% Componentes R, G e B da imagem iguais, formando uma imagem em tons de
% cinza que é o mapa de altura
%imagem(1:disc_x, 1:disc_y, 1) = ap;
%imagem(1:disc_x, 1:disc_y, 2) = ap;
%imagem(1:disc_x, 1:disc_y, 3) = ap;
%imagem(1:disc_x, 1:disc_y, 4) = 1;

% Salva a imagem do mapa de altura para ser utilizada no ShaderLabs
%imwrite(imagem(:,:,1:3), 'mapa.png', 'png', 'alpha', imagem(:,:,4));

%vert = fopen('Oficial.vert', 'wt');
%fprintf(vert, '#define ZERO %f\n', zero_normalizado);
%fprintf(vert, '#define SCALE %f\n\n', delta_x/2.0);
%fclose(vert);
%system('more temp.vert >> Oficial.vert');

% open a file for writing
fid = fopen('wave_data.txt', 'wt');

fprintf(fid, '%f %f %d\n', x_inicial, x_final, disc_x);
fprintf(fid, '%f %f %d\n', y_inicial, y_final, disc_y);
fprintf(fid, '%f %f %d\n', t_inicial, t_final, disc_t);

for i =  1:disc_t
    for j = 1: disc_x
        for k = 1: disc_y
            fprintf(fid, '%f ',up(j,k,i));
        end
        fprintf(fid, '\n');
    end
end

for i = 1: disc_x
        for j = 1: disc_y
            fprintf(fid, '%f ',cp(i,j));
        end
        fprintf(fid, '\n');
    end
fclose(fid);

