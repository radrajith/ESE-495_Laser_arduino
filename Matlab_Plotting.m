%%plotting the data
input = xlsread('ESE 499 laser characteristics.xlsx',7);

file1 = input(2:size(input,1),1);    
file2 = input(2:size(input,1),8);
file3 = input(2:size(input,1),15);

figure(1);
hold on;
%% power overlay
file = file1;
time = 3;
period = .1;
delta = find(file == 19.59, 1,'first');
adjust = delta - (find(file == max(file),1,'last') - (time*1000*period));
delta = delta - adjust;
w = .90;
pow = 5;
size_g =1500;
y=[];
n=1;m=1;

for i=.005:.005:(time-(period+0.005))
    if 0==mod(n,20)
        m = m+1;
    end;
    y(n) = pow*w*m;
    n = n+1;
end;
y = [zeros([1 (delta-1)]) y];
y = [y zeros([1 (size_g - size(y,2))])];
endpt = (time*100)+delta;
t = linspace(delta,endpt, n);
m = 1:1:delta-1;
t = [m , t];
t = [t, zeros([1 (size(y,2) - size(t,2))])];
yyaxis right, plot(t, y,'-'), ylabel('Energy(mJ)');
%%
%subplot(2,2,1),
%plot(file(1:41), file2(1:41)),text(4000,5000,'y = 1.2756x - 1089.2'),xlabel('Current (mA)'), ylabel('Power (mW)'), title('Power vs Current'), grid on;;
%subplot(2,2,2),plot(file2(50:700)),xlabel('No of Points'), ylabel('Temperature(°C)'), title('(2) Orange peel [1.87mm]'), grid on;;
%subplot(2,2,3);plot(file3(50:700)),xlabel('No of Points'), ylabel('Temperature(°C)'), title('(3) Orange peel [1.87mm]'), grid on;;

yyaxis left, plot(file(1:size(file)),'-'),xlabel('No of Points'), ylabel('Temperature(°C)'), title('(1) Orange peel [1.14mm]'), grid on;
hold off;
%figure(2);
%plot(diff(file(1:350)));
%xlabel('No of Points'), ylabel('Temperature(°C)'), title('(2) Banana peel [2.18mm] - Derivative'), grid on;

% pulses = 20; 
% t = .001:.001:period;
% x = rectpuls(t,2*w*period);
% t = repmat(t', pulses,1);
% x = repmat(x', pulses,1);
% plot(5*x);

    
