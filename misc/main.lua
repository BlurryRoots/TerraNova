local C = terralib.includec ("knurpsel.h")

terra main()
	print (C.knurpsel (12, 21))
end

main ()
