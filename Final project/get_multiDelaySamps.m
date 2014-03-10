function [ delay1, delay2, delay3 ] = get_multiDelaySamps( first_delay_sec, sampleRate )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

delay1 = first_delay_sec*sampleRate;
delay2 = delay1*1.86;
delay3 = delay2*2.72;
end

