%%%%%%%%%%%%%           2016707079 하상천  
%%%%%%%%%%%%%          (6,3) Linear Block Code       
        
fprintf('2016707079 하상천\n\n');

NUM = 1000;
N1 = 6;
K1 = 3;
SEED = 1;

I3 = eye(3);
P = [1 1 0; 0 1 1; 1 0 1];
BITS = NUM * K1;

prompt = 'What is the oversampling ratio value?  ';
over_sampling_ratio = input(prompt);

message = ones(NUM, K1);
generator = make_generator(P,I3);
parity_check = make_parity_check(P,I3);

%%%% scrambling
scrambled_code = Scrambling(message, NUM, K1);
%%%% encoding
codeword = mod(scrambled_code * generator, 2);

%%%% symbol mapping  (bit -> symbol (2 bits -> 1 symbol))
symbol_idx = symbol_mapping(NUM, N1, codeword);
%%%% pulse shaping
tx_pulse_out = pulse_shaping(NUM, N1, over_sampling_ratio, symbol_idx);

rx_pulse_out = tx_pulse_out + randn(1,length(tx_pulse_out));

%%%% de_pulse shaping
rx_symbol_idx = de_pulse_shaping(symbol_idx, over_sampling_ratio, rx_pulse_out);
%%%% de_symbol mapping
rx_codeword = de_symbol_mapping(NUM, N1, rx_symbol_idx);

%%%% decoding
syndromes = mod(rx_codeword * parity_check, 2);
finish_message = Flipping(NUM, syndromes, rx_codeword);
final_msg = finish_message(:,4:6);
%%%% descrambling
descrambled_code = Scrambling(final_msg, NUM, K1);
%%%% error analysis
[bit_error_count, block_error_count] = error_calculation(NUM, descrambled_code, message);

BER = bit_error_count / BITS;
BLER = block_error_count / NUM;

fprintf('(6,3) Linear Block Code BER은 %.4f 입니다.\n',BER)
fprintf('(6,3) Linear Block Code BLER은 %.4f 입니다.\n',BLER)





%%%%%%%%%%%%%%%%          (7,3) Cyclic Code       
N2 = 7;
K2 = 3;
BITS = NUM * K2;
generator_polynomial = [1 1 1 0 1];
message2 = ones(NUM, K2);

%%%% scrambling
scrambled_code2 = Scrambling(message2, NUM, K2);    
%%%% encoding
codeword2 = make_codeword2(NUM, N2, scrambled_code2, generator_polynomial);

%%%% symbol mapping  (bit -> symbol (2 bits -> 1 symbol))
symbol_idx2 = symbol_mapping(NUM, N2, codeword2);
%%%% pulse shaping
tx_pulse_out2 = pulse_shaping(NUM, N2, over_sampling_ratio, symbol_idx2);

rx_pulse_out2 = tx_pulse_out2 + randn(1,length(tx_pulse_out2));

%%%% de_pulse shaping
rx_symbol_idx2 = de_pulse_shaping(symbol_idx2, over_sampling_ratio, rx_pulse_out2);
%%%% de_symbol mapping
rx_codeword2 = de_symbol_mapping(NUM, N2, rx_symbol_idx2);

%%%% decoding
finish_message2 = Flipping2(NUM, rx_codeword2, generator_polynomial);
final_msg2 = finish_message2(:,5:7);

%%%% descrambling
descrambled_code2 = Scrambling(final_msg2, NUM, K2);

%%%% error analysis
[bit_error_count2, block_error_count2] = error_calculation2(NUM, descrambled_code2, message2);

BER2 = bit_error_count2 / BITS;
BLER2 = block_error_count2 / NUM;

fprintf('(7,3) Cyclic Code BER은 %.4f 입니다.\n',BER2)
fprintf('(7,3) Cyclic Code BLER은 %.4f 입니다.\n',BLER2)





% symbol_mapping
function symbol_idx = symbol_mapping(NUM, num, codeword)
sym_idx = zeros(1, NUM * num);
for i = 1: NUM
    sym_idx((i-1)*num+1:num*i) = codeword(i, :);
end
symbol_idx = sym_idx(1:2:end)*2 + sym_idx(2:2:end);
end
% de_symbol_mapping
function rx_codeword = de_symbol_mapping(NUM, num, rx_symbol_idx)
rx_codeword = zeros(NUM, num);
de_sym_idx = zeros(1, NUM *num);
for i = 1:length(rx_symbol_idx)
    de_sym_idx((i-1)*2+1:i*2) = [floor(rx_symbol_idx(i)/2) mod(rx_symbol_idx(i),2)];
end
for i = 1:NUM
    rx_codeword(i,:) = de_sym_idx((i-1)*num+1:i*num);
end
end

% pulse_shaping
function tx_pulse_out = pulse_shaping(NUM, num, over_sampling_ratio, symbol_idx)
tx_pulse_out = zeros(1, NUM * num * over_sampling_ratio / 2 );  % 2비트니까
ratio = floor(over_sampling_ratio/2);
if mod(over_sampling_ratio,2) == 0
    up_tri = linspace(0,2,over_sampling_ratio);
    up_tri = up_tri(1:ratio);
    down_tri = up_tri(end:-1:1);
    tri_pulse = [up_tri down_tri];
else
    up_tri = linspace(0,1,ratio +1);
    down_tri = up_tri(end-1:-1:1);
    tri_pulse = [up_tri down_tri];
end
for i = 1:length(symbol_idx)
    tx_pulse_out((i-1)*over_sampling_ratio+1:over_sampling_ratio*i) = symbol_idx(i) * tri_pulse;
end
end
% de_pulse_shaping
function rx_symbol_idx = de_pulse_shaping(symbol_idx, over_sampling_ratio, tx_pulse_out)
rx_symbol_idx = zeros(1,length(symbol_idx));
for i = 1:length(symbol_idx)
    sum = 0;
    for j = 1 : over_sampling_ratio
        sum =  tx_pulse_out((over_sampling_ratio)*(i-1) +j) + sum;
    end
    avg = sum / over_sampling_ratio;
    if avg <0.3333
        rx_symbol_idx(i) = 0;
    elseif (0.3333<= avg) && (avg < 0.6666)
        rx_symbol_idx(i) = 1;
    elseif (0.6666<= avg) && (avg < 1)
        rx_symbol_idx(i) = 2;
    elseif (1<= avg)
        rx_symbol_idx(i) = 3;
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
function [bit_error_count, block_error_count] = error_calculation(NUM, finish_message, message)
bit_error_count = 0;
block_error_count = 0;
for number = 1:NUM
    flag = 0;
    if message(number,1) ~= finish_message(number,1)
        bit_error_count = bit_error_count + 1;
        flag = 1;
    end
    if message(number,2) ~= finish_message(number,2)
        bit_error_count = bit_error_count + 1;
        flag = 1;
    end
    if message(number,3) ~= finish_message(number,3)
        bit_error_count = bit_error_count + 1;
        flag = 1;    
    end
    if flag == 1
        block_error_count = block_error_count + 1;
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


% Cyclic Code Functions
function codeword2 = make_codeword2(NUM, N2, message2, generator_polynomial) 
four_zeros = zeros(1,4);
codeword2 = zeros(NUM,N2);
for number = 1:NUM
    msg2 = message2(number,:);
    mul_message = [four_zeros, msg2];
    [~, remainder] = gfdeconv(mul_message, generator_polynomial);
    i = size(remainder);
    idx = i(2);
    if idx == 1
        codeword = [remainder(idx) 0 0 0 msg2];
    elseif idx == 2
        codeword =[remainder(idx-1) remainder(idx) 0 0 msg2];
    elseif idx == 3
        codeword = [remainder(idx-2) remainder(idx-1) remainder(idx) 0 msg2];
    else
        codeword = [remainder, msg2];
    end
    codeword2(number,:) = codeword;
end
end
function finish_message2 = Flipping2(NUM, received_codeword2, generator_polynomial)
for number = 1:NUM
    [~, syndrome2] = gfdeconv(received_codeword2(number,:), generator_polynomial);
    i = size(syndrome2);
    idx = i(2);
    if idx == 1
        syndrome2 = [syndrome2(idx) 0 0 0];
    elseif idx == 2
        syndrome2 =[syndrome2(idx-1) syndrome2(idx) 0 0];
    elseif idx == 3
        syndrome2 = [syndrome2(idx-2) syndrome2(idx-1) syndrome2(idx) 0];
    end
    if syndrome2 == [0 0 0 0]
    elseif syndrome2 == [0 0 0 1]
        received_codeword2(number,4) = ~received_codeword2(number,4);
    elseif syndrome2 == [0 0 1 0]
        received_codeword2(number,3) = ~received_codeword2(number,3);
    elseif syndrome2 == [0 0 1 1]
        received_codeword2(number,5) = ~received_codeword2(number,5);
        received_codeword2(number,7) = ~received_codeword2(number,7);
    elseif syndrome2 == [0 1 0 0]
        received_codeword2(number,2) = ~received_codeword2(number,2);
    elseif syndrome2 == [0 1 0 1]
        received_codeword2(number,1) = ~received_codeword2(number,1);
        received_codeword2(number,7) = ~received_codeword2(number,7);
    elseif syndrome2 == [0 1 1 0]
        received_codeword2(number,4) = ~received_codeword2(number,4);
        received_codeword2(number,6) = ~received_codeword2(number,6);
    elseif syndrome2 == [0 1 1 1]
        received_codeword2(number,6) = ~received_codeword2(number,6);
    elseif syndrome2 == [1 0 0 0]
        received_codeword2(number,1) = ~received_codeword2(number,1);
    elseif syndrome2 == [1 0 0 1]
        received_codeword2(number,7) = ~received_codeword2(number,7);
        received_codeword2(number,2) = ~received_codeword2(number,2);
    elseif syndrome2 == [1 0 1 0]
        received_codeword2(number,7) = ~received_codeword2(number,7);
        received_codeword2(number,6) = ~received_codeword2(number,6);
    elseif syndrome2 == [1 0 1 1]
        received_codeword2(number,1) = ~received_codeword2(number,1);
        received_codeword2(number,3) = ~received_codeword2(number,3);
        received_codeword2(number,4) = ~received_codeword2(number,4);
    elseif syndrome2 == [1 1 0 0]
        received_codeword2(number,7) = ~received_codeword2(number,7);
        received_codeword2(number,4) = ~received_codeword2(number,4);
    elseif syndrome2 == [1 1 0 1]
        received_codeword2(number,7) = ~received_codeword2(number,7);
    elseif syndrome2 == [1 1 1 0]
        received_codeword2(number,5) = ~received_codeword2(number,5);    
    elseif syndrome2 == [1 1 1 1]
        received_codeword2(number,7) = ~received_codeword2(number,7);
        received_codeword2(number,3) = ~received_codeword2(number,3);  
    end
end
finish_message2 = received_codeword2;
end
function [bit_error_count2, block_error_count2] = error_calculation2(NUM, finish_message2, message2)
bit_error_count2 = 0;
block_error_count2 = 0;
for number = 1:NUM
    flag = 0;
    if message2(number,1) ~= finish_message2(number,1)
        bit_error_count2 = bit_error_count2 + 1;
        flag = 1;
    end
    if message2(number,2) ~= finish_message2(number,2)
        bit_error_count2 = bit_error_count2 + 1;
        flag = 1;
    end
    if message2(number,3) ~= finish_message2(number,3)
        bit_error_count2 = bit_error_count2 + 1;
        flag = 1;    
    end
    if flag == 1
        block_error_count2 = block_error_count2 + 1;
    end
end
end
