
N = 5; %Количество регистров
len_pos = 2^N - 1; %Длина последовательности
%задаем регистры
register_x = [0, 1, 0, 1, 1];
register_y = [1, 0, 0, 1, 0];
register_x1 = [0, 1, 1, 0, 0];
register_y1 = [0, 1, 1, 0, 1];

% Генерация последовательности Голда и измененной последовательности
dis = sprintf("\nFirst Gold''s sequencen\n");
random_sequence = GoldSeq(register_x, register_y, len_pos);

dis2 = sprintf("\nSecond Gold''s sequence (x = 12, y = 13):\n");

modified_sequence = GoldSeq(register_x1, register_y1, len_pos);

%выводим последовательности на экран
for i = 1:len_pos
    dis = sprintf("%s %d", dis, random_sequence(i));
    dis2 = sprintf("%s %d", dis2, modified_sequence(i));
end
disp(dis);
disp(newline);
disp(dis2);
%копируем первую последовательность на массив для сдвига
shift_random_sequence = random_sequence;

% Находим автокорреляцию через xcorr(x,x), тк встроенная функция не работает
[cor, lag]=xcorr(random_sequence,random_sequence);
dis = sprintf("\nСдвиг");
for i = 1:len_pos
    dis = sprintf("%s|%2d", dis,i);
end
dis = sprintf("%s|корреляция|", dis);

%половина массива xcorr
t = (0:31);
corrMass = (0:31);
%считаем автокорреляцию вручную
for i = 0:len_pos
    dis = sprintf('%s\n', dis);
    dis = sprintf("%s| %2d ",dis, i);
    for j = 1:len_pos
        dis = sprintf("%s|%2d", dis, shift_random_sequence(j));
    end
    %[acf,lags] = autocorr(random_sequence);
	%Функция для рассчета автокорреляции вручную
    corr = corrXY(random_sequence, shift_random_sequence, len_pos);
    	%заполнение массива значениями корреляции
	corrMass(i+1) = corr/len_pos;
    dis = sprintf("%s| %5.2f", dis, corr/len_pos);
    %Сдвиг последовательности
    shift_random_sequence = circshift(random_sequence, [0, i+1]);
end
disp(dis);
% расчет корреляции между первой и второй последовательностями
[cor1, lag1]=xcorr(random_sequence,modified_sequence);
dis = sprintf("\nВзаимная корреляция между первоначальной и новосозданной последовательностью >> %.0f", cor1(len_pos));
disp(dis);
%Вывод графиков
subplot(2, 1, 1);
plot(t,corrMass);
xlabel("Сдвиг");
ylabel("Amplitude");
title("Ручная автокорреляция");
subplot(2, 1, 2);
plot(lag,cor);
xlabel("lag");
ylabel("Amplitude");
title("Замена автокорреляции xcorr(x,x)");

%Функция для генерации последовательности голда
function sequence = GoldSeq(register_x, register_y, len_pos)
    sequence = zeros(1, len_pos);
    for i = 1:len_pos
        sequence(i) = mod(register_x(5) + register_y(5), 2);
        [register_x, register_y] = shift(register_x, register_y);
    end
end
%Функция для рассчета автокорреляции
function corr = corrXY(random_sequence, shift_random_sequence, len_pos)
    corr = 0;
    for i = 1:len_pos
        if random_sequence(i) == shift_random_sequence(i)
            corr = corr+1;
        else 
            corr = corr-1;
        end
    end
end
%Функция для сдвига регистров
function [register_x, register_y] = shift(register_x, register_y)
    res_x = mod(register_x(3) + register_x(4), 2);
    res_y = mod(register_y(2) + register_y(3), 2);
    register_x = circshift(register_x, [0, 1]);
    register_x(1) = res_x;
    register_y = circshift(register_y, [0, 1]);
    register_y(1) = res_y;
end
