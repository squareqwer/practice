-module(set).
-vsn(1234).
-author({shinigami}).
-email(squareqwer@gmail.com).
-purpose("test attributes").
-export([fab/1,
        extract/2]).

fab(1) ->
    1;
fab(N) ->
    N+fab(N-1).


extract(File,Key) ->
    case beam_lib:chunks(File, [attributes]) of   
            {ok, {_Module, [{attributes, L}]}} ->
                 case lookup(Key, L) of 
                       {ok, Val}->
                           Val;   
                     error->
                         exit(bagFile)
                 end;            
        _ ->
            exit(bagFile)
    end.


lookup(Key, [{Key,Val}|_]) ->
    {ok, Val};
lookup(Key,[_|T]) ->
    lookup(Key, T);
lookup(_, []) ->
    error.

            
