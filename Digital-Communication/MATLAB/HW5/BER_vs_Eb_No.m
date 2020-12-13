%%%%%%%%%%%%%           2016707079 하상천  
%%%%%%%%%%%%%          (6,3) Linear Block Code       
        
fprintf('2016707079 하상천\n\n');

prompt = 'What is the roll-off factor value? (default : 1)  ';
roll_off = input(prompt);
prompt = 'What is the symbol_period value? (default : 8)  ';
symbol_period = input(prompt);
prompt = 'What is the oversampling ratio value? (propagation channel 때문에 짝수)(default : 16)  ';
over_sampling_ratio = input(prompt);
prompt = 'What is the sampling point value? (default : 1)  ';
sampling_point = input(prompt);
prompt = 'What is the propagation channel(multi path) ISI value? (default : 1/2)  ';
propagation_ISI = input(prompt);

NUM = 2*10^5;
N1 = 6;
K1 = 3;
SEED = 1;
TRUE = 1;
FALSE = 0;
I3 = eye(3);
P = [1 1 0; 0 1 1; 1 0 1];
BITS = NUM * K1;
message = ones(NUM, K1);
generator = make_generator(P,I3);
parity_check = make_parity_check(P,I3);
hs = square_root_raised_cosine(roll_off, symbol_period, over_sampling_ratio);

Eb_N0_dB = [-5:20];
Es_N0_dB_16QAM  = Eb_N0_dB + 10*log10(4); 
Es_N0_dB_QPSK = Eb_N0_dB + 10*log10(2);
BER_MULTI_PATH_16QAM = zeros(1,26);
BER_16QAM = zeros(1,26);
BER_MULTI_PATH_QPSK = zeros(1,26);
BER_QPSK = zeros(1,26);

%%%%%%%%%%%%%%%% 16 QAM
for i = 1 :2
    if i == 1
        multi_path_use = TRUE;
    elseif i ==2
        multi_path_use = FALSE;
    end
for idx = 1:length(SNR_dB)
    %%%% scrambling
    scrambled_code = Scrambling(message, NUM, K1);
    %%%% encoding
    codeword = mod(scrambled_code * generator, 2);

    %%%% symbol mapping  (bit -> symbol (4 bits -> 1 symbol))
    symbol_idx = symbol_mapping_16QAM(NUM, N1, codeword);
    %%%% pulse shaping
    tx_pulse_out = pulse_shaping_16QAM(over_sampling_ratio, symbol_idx, hs);

    %%%% propagation channel
    if multi_path_use == TRUE
        tx_pulse_out = propagation(tx_pulse_out, over_sampling_ratio, propagation_ISI);
    end
    NOISE = 1/sqrt(2)*([randn(1,length(tx_pulse_out)) + 1i*randn(1,length(tx_pulse_out))]);
    rx_pulse_out = tx_pulse_out + 10^(-Es_N0_dB_16QAM(idx)/20)*NOISE ;

    %%%% de_pulse shaping
    rx_symbol_idx= de_pulse_shaping_16QAM(over_sampling_ratio, rx_pulse_out, hs, symbol_period, sampling_point);
    %%%% de_symbol mapping
    rx_codeword  = de_symbol_mapping_16QAM(NUM, N1, rx_symbol_idx);

    %%%% decoding
    syndromes = mod(rx_codeword * parity_check, 2);
    finish_message = Flipping(NUM, syndromes, rx_codeword);
    final_msg = finish_message(:,4:6);
    %%%% descrambling
    descrambled_code = Scrambling(final_msg, NUM, K1);
    %%%% error analysis
    bit_error_count = error_calculation(NUM, descrambled_code, message);
    if i == 1
        BER_MULTI_PATH_16QAM(idx) = bit_error_count / BITS;
    elseif i ==2
        BER_16QAM(idx) = bit_error_count / BITS;
    end
end
end
%%%%%%%%%%%%%%%% QPSK
for i = 1 :2
    if i == 1
        multi_path_use = TRUE;
    elseif i ==2
        multi_path_use = FALSE;
    end
for idx = 1:length(SNR_dB)
    %%%% scrambling
    scrambled_code = Scrambling(message, NUM, K1);
    %%%% encoding
    codeword = mod(scrambled_code * generator, 2);

    %%%% symbol mapping  (bit -> symbol (2 bits -> 1 symbol))
    symbol_idx = symbol_mapping_QPSK(NUM, N1, codeword);
    %%%% pulse shaping
    tx_pulse_out = pulse_shaping_QPSK(over_sampling_ratio, symbol_idx, hs);

    %%%% propagation channel
    if multi_path_use == TRUE
        tx_pulse_out = propagation(tx_pulse_out, over_sampling_ratio, propagation_ISI);
    end
    NOISE = 1/sqrt(2)*([randn(1,length(tx_pulse_out)) + 1i*randn(1,length(tx_pulse_out))]);
    rx_pulse_out = tx_pulse_out + 10^(-Es_N0_dB_QPSK(idx)/20)*NOISE ;

    %%%% de_pulse shaping
    rx_symbol_idx = de_pulse_shaping_QPSK(over_sampling_ratio, rx_pulse_out, hs, symbol_period, NUM, N1, sampling_point);
    %%%% de_symbol mapping
    rx_codeword = de_symbol_mapping_QPSK(NUM, N1, rx_symbol_idx);

    %%%% decoding
    syndromes = mod(rx_codeword * parity_check, 2);
    finish_message = Flipping(NUM, syndromes, rx_codeword);
    final_msg = finish_message(:,4:6);
    %%%% descrambling
    descrambled_code = Scrambling(final_msg, NUM, K1);
    %%%% error analysis
    bit_error_count = error_calculation(NUM, descrambled_code, message);

    if i == 1
        BER_MULTI_PATH_QPSK(idx) = bit_error_count / BITS;
    elseif i ==2
        BER_QPSK(idx) = bit_error_count / BITS;
    end
end
end

semilogy(SNR_dB,BER_MULTI_PATH_16QAM,'mx-','LineWidth', 2);
hold on;
semilogy(SNR_dB,BER_16QAM,'bs-','LineWidth', 2);
hold on;
semilogy(SNR_dB,BER_MULTI_PATH_QPSK,'r-','LineWidth', 2);
hold on;
semilogy(SNR_dB,BER_QPSK,'y-','LineWidth', 2);
axis([-5 20 10^-5 1]);
grid on;
legend('16 QAM(Multi path)', '16 QAM', 'QPSK(Multi path)', 'QPSK');
xlabel('Eb/No[dB]');
ylabel('Bit Error Rate');
title('Bit error probability curve');



%%%%%%%%%%%%%%%%%%%%%%% function %%%%%%%%%%%%%%%%%%%%%%%%%%%

% propagation channel
function add_propagation = propagation(tx_pulse_out, over_sampling_ratio,propagation_ISI)
h = zeros(1, over_sampling_ratio/2 +1);
h(1) = 1;
h(over_sampling_ratio/2 +1)=propagation_ISI;
add_propagation = conv(h,tx_pulse_out);
end
% square_root_raised_cosine
function hs = square_root_raised_cosine(roll_off, symbol_period, over_sampling_ratio)
hs = rcosfir(roll_off, [-symbol_period symbol_period], over_sampling_ratio, 1, 'sqrt');
end



%%%%%%% 16 QAM function %%%%%%
% symbol_mapping
function symbol_idx = symbol_mapping_16QAM(NUM, num, codeword)
sym_idx = zeros(1, NUM * num);
for i = 1: NUM
    sym_idx((i-1)*num+1:num*i) = codeword(i, :);
end
LUT = [-3 -1 1 3];
real = sym_idx(1:4:end)*2 + sym_idx(2:4:end);
img = sym_idx(3:4:end)*2 + sym_idx(4:4:end);
reals = LUT(real+1);
imgs = LUT(img+1);
symbol_idx = reals(1:1:end) + 1i*imgs(1:1:end);
symbol_idx= symbol_idx/sqrt(10);
end
% de_symbol_mapping
function rx_codeword = de_symbol_mapping_16QAM(NUM, num, rx_symbol_idx)
rx_codeword = zeros(NUM, num);
de_sym_idx = zeros(1, NUM * num);
real_binary = zeros(1,NUM *num/2);
imag_binary = zeros(1,NUM *num/2);
real_values = real(rx_symbol_idx)*sqrt(10);
real_values = 2*floor(real_values/2)+1;
imag_values = imag(rx_symbol_idx)*sqrt(10);
imag_values =  2*floor(imag_values/2)+1;
for i =1:length(real_values)
    if real_values(i)<= -2
        real_binary(2*(i-1) +1) = 0;
        real_binary(2*(i-1) +2) = 0;
    elseif (real_values(i)>-2) && (real_values(i)<0)
        real_binary(2*(i-1) +1) = 0;
        real_binary(2*(i-1) +2) = 1;
    elseif (real_values(i)>=0) && (real_values(i)<2)
        real_binary(2*(i-1) +1) = 1;
        real_binary(2*(i-1) +2) = 0;
    elseif (real_values(i)>= 2)
        real_binary(2*(i-1) +1) = 1;
        real_binary(2*(i-1) +2) = 1;           
    end   
end
for i =1:length(imag_values)
    if imag_values(i)<= -2
        imag_binary(2*(i-1) +1) = 0;
        imag_binary(2*(i-1) +2) = 0;
    elseif (imag_values(i)>-2) && (imag_values(i)<0)
        imag_binary(2*(i-1) +1) = 0;
        imag_binary(2*(i-1) +2) = 1;
    elseif (imag_values(i)>=0) && (imag_values(i)<2)
        imag_binary(2*(i-1) +1) = 1;
        imag_binary(2*(i-1) +2) = 0;
    elseif (imag_values(i)>= 2)
        imag_binary(2*(i-1) +1) = 1;
        imag_binary(2*(i-1) +2) = 1;           
    end   
end
for i = 1:length(real_binary)/2
    de_sym_idx(4*(i-1)+1) = real_binary(2*(i-1)+1);
    de_sym_idx(4*(i-1)+2) = real_binary(2*(i-1)+2);
    de_sym_idx(4*(i-1)+3) = imag_binary(2*(i-1)+1);
    de_sym_idx(4*(i-1)+4) = imag_binary(2*(i-1)+2);
end
    
for i = 1:NUM
    rx_codeword(i,:) = de_sym_idx((i-1)*num+1:i*num);
end
end
% pulse_shaping
function tx_pulse_out = pulse_shaping_16QAM(over_sampling_ratio, symbol_idx, hs)
symbol_idx_ovr(1:over_sampling_ratio:over_sampling_ratio*length(symbol_idx))=symbol_idx;
tx_pulse_out = conv(hs,symbol_idx_ovr);
end
% de_pulse_shaping
function rx_symbol_idx = de_pulse_shaping_16QAM(over_sampling_ratio, rx_pulse_out, hs, symbol_period, sampling_point)
mf_out=conv(rx_pulse_out,hs);
if sampling_point == 1
    rx_sampling_point_out = mf_out(sampling_point:over_sampling_ratio:end);
    rx_symbol_idx = rx_sampling_point_out(symbol_period*2+1:end-symbol_period*2);
else
    rx_sampling_point_out = mf_out(sampling_point:over_sampling_ratio:end);
    rx_symbol_idx = rx_sampling_point_out(symbol_period*2:end-symbol_period*2);
end
end



%%%%%% QPSK function %%%%%
% symbol_mapping
function symbol_idx = symbol_mapping_QPSK(NUM, num, codeword)
sym_idx = zeros(1, NUM * num);
for i = 1: NUM
    sym_idx((i-1)*num+1:num*i) = codeword(i, :);
end
sym_idx = 1-2*sym_idx;
symbol_idx = sym_idx(1:2:end) +1i*sym_idx(2:2:end);
symbol_idx= symbol_idx/sqrt(2);
end
% de_symbol_mapping
function rx_codeword = de_symbol_mapping_QPSK(NUM, num, rx_symbol_idx)
rx_codeword = zeros(NUM, num);
de_sym_idx = zeros(1, NUM *num);
for i = 1:length(rx_symbol_idx)
    de_sym_idx((i-1)*2+1:i*2) = [real(rx_symbol_idx(i)) imag(rx_symbol_idx(i))];
end
for i = 1:length(de_sym_idx)
    if de_sym_idx(i) == -1
        de_sym_idx(i) = 1;
    else 
        de_sym_idx(i) = 0;
    end
end
for i = 1:NUM
    rx_codeword(i,:) = de_sym_idx((i-1)*num+1:i*num);
end
end
% pulse_shaping
function tx_pulse_out = pulse_shaping_QPSK(over_sampling_ratio, symbol_idx, hs) 
symbol_idx_ovr(1:over_sampling_ratio:over_sampling_ratio*length(symbol_idx))=symbol_idx;
tx_pulse_out = conv(hs,symbol_idx_ovr);
end
% de_pulse_shaping
function rx_symbol_idx = de_pulse_shaping_QPSK(over_sampling_ratio, rx_pulse_out, hs, symbol_period, NUM, N, sampling_point)
MAX = NUM *N /2;  % 2bits
mf_out=conv(rx_pulse_out,hs);
if sampling_point == 1
    rx_sampling_point_out = mf_out(sampling_point:over_sampling_ratio:end);
    rx_symbol_idx = rx_sampling_point_out(symbol_period*2+1:end-symbol_period*2);
else
    rx_sampling_point_out = mf_out(sampling_point:over_sampling_ratio:end);
    rx_symbol_idx = rx_sampling_point_out(symbol_period*2:end-symbol_period*2);
end
for n = 1: MAX
    if (angle(rx_symbol_idx(n)) >= 0) && (angle(rx_symbol_idx(n)) < pi/2)
        rx_symbol_idx(n) = 1+1i;
    elseif (pi/2 <= angle(rx_symbol_idx(n))) && (angle(rx_symbol_idx(n)) < pi)
        rx_symbol_idx(n) = -1+1i;
    elseif (-pi/2 <= angle(rx_symbol_idx(n))) && (angle(rx_symbol_idx(n)) < 0)
        rx_symbol_idx(n) = 1-1i;
    elseif ( -pi <= angle(rx_symbol_idx(n))) && (angle(rx_symbol_idx(n)) < -pi/2)
        rx_symbol_idx(n) = -1-1i;
    end       
end
end


% Scrambling
function regs = make_register()
    regs = zeros(1,18);
    regs(end) = 1;
    regs(end-5) = 1;
    regs(4) = 1;
end
function output = Scrambling(message, NUM, num)
    regs1 = make_register();
    regs2 = make_register();
    output = zeros(NUM, num);
    for i = 1:NUM
        for j = 1:num
            scr_code1 = mod((regs1(4) + regs1(6) + regs1(15)),2);
            scr_code2 = mod((regs2(6)+regs2(7)+regs2(9)+regs2(10)+regs2(11)+regs2(12)+regs2(13)+regs2(14)+regs2(15)+regs2(16)),2);
            Q = mod(scr_code1 + scr_code2 ,2);
            output(i,j) = mod(message(i,j) + Q , 2);
            regs1(2:end) = regs1(1:end-1);
            regs2(2:end) = regs2(1:end-1);
            regs1(1) = scr_code1;
            regs2(1) = scr_code2;
        end
    end
end

% Linear Block Code Functions
function bit_error_count = error_calculation(NUM, finish_message, message)
bit_error_count = 0;
for number = 1:NUM
    if message(number,1) ~= finish_message(number,1)
        bit_error_count = bit_error_count + 1;
    end
    if message(number,2) ~= finish_message(number,2)
        bit_error_count = bit_error_count + 1;
    end
    if message(number,3) ~= finish_message(number,3)
        bit_error_count = bit_error_count + 1;
    end
end
end
function finish_message = Flipping(NUM, syndromes, received_codeword)
for number = 1:NUM
    syndrome = syndromes(number,:);
    if syndrome == [0 0 0]
        continue
    elseif syndrome == [0 0 1]
        received_codeword(number,3) = ~received_codeword(number,3);
    elseif syndrome == [0 1 0]
        received_codeword(number,2) = ~received_codeword(number,2);
    elseif syndrome == [0 1 1]
        received_codeword(number,5) = ~received_codeword(number,5);
    elseif syndrome == [1 0 0]
        received_codeword(number,1) = ~received_codeword(number,1);
    elseif syndrome == [1 0 1]
        received_codeword(number,6) = ~received_codeword(number,6);
    elseif syndrome == [1 1 0]
        received_codeword(number,4) = ~received_codeword(number,4);
    elseif syndrome == [1 1 1]
        received_codeword(number,2) = ~received_codeword(number,2);
        received_codeword(number,6) = ~received_codeword(number,6);
    end
end
finish_message = received_codeword;
end
function generator = make_generator(P,I3)
    generator = [P,I3];
end
function parity_check = make_parity_check(P,I3)
    parity_check = [I3;P];
end


