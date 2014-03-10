[input_wav,fs] = wavread('/Users/xinquanzhou/Desktop/sweep.wav');

[numSample,numChannel] = size(input_wav);


% delay with the interpolated value(maybe linear interpolation)

for i = 1:numChannel
    input_stream = input_wav(:,i);
    [d1,d2,d3] = get_multiDelaySamps(0.07,fs);
    output_stream = InterpolateDelay(input_stream,d1);
    output_wav(:,i) = output_stream;
end

