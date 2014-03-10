function output_stream = InterpolateDelay(input_stream,delay_sample)

len = length(input_stream);
L = ceil(delay_sample);
output_stream = zeros(1,len);
Delay_line = zeros(1,L);
for i = 1:len
    n = floor(delay_sample);
    frac = delay_sample - n;
    Delay_line = [input_stream(i),Delay_line(1:L-1)];
    output_stream(i) = Delay_line(n+1)*frac+Delay_line(n)*(1-frac);
end

end
