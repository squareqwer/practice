function p()  
    print("Hello World")  
end  


co = coroutine.create(p)  
print(co)               --> thread: 003FBBF0  
print(coroutine.status(co))     --> suspended  
coroutine.resume(co)            --> Hello World  
print(coroutine.status(co))     --> dead  

co2 = coroutine.create(function(a, b)  
        coroutine.yield(a * b, a + b)  
    end)  
print(coroutine.resume(co2, 2, 2009))  

