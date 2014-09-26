#! /usr/bin/env ruby

def showusage
puts <<EOF
	confusionmatrix <test file> <prediction from libsvm>
EOF
exit
end

def read_test_file(file)
	test_file_results = {}
	line_num = 0
	File.open(file) do |f|
		f.lines.each do |line|
			line_num += 1
			test_file_results[line_num] = line.split(',').first.to_i
		end
	end
	return test_file_results
end

def read_predict_file(file)
	predict_file_results = {}
	line_num = 0
	File.open(file) do |f|
		f.lines.each do |line|
			line_num += 1
			predict_file_results[line_num] = line.chomp.to_i
		end
	end
	return predict_file_results
end

def calc_confustion(classes,actual,predict)
	keys = classes.keys
	#confusion matrix stores actual => predicted
	confusionmatrix = {}
	classes.each{ |key, value| 
		confusionmatrix[key] = {}
		keys.each{ |i| confusionmatrix[key][i] = 0}
	}

	actual.each{ |key, value| 
		confusionmatrix[value][predict[key]] = confusionmatrix[value][predict[key]] + 1 
	}

	return confusionmatrix
end

def create_table_header(table_width,column_width,classes)
	puts "#{" "*(column_width-1)}+#{"-"*(table_width-column_width-1)}+"
	puts "#{" "*(column_width-1)}|#{"%-#{table_width-column_width-1}.#{table_width-column_width-1}s" % "Predicted"}|"
	puts "+#{"-"*(column_width-2)}+#{"-"*(table_width-column_width-1)}+"
	column_names = ""
	classes.each{ |key, value| column_names << "#{"%-#{column_width-1}.#{column_width-1}s" % value}|"}
	puts "|#{"%-#{column_width-2}.#{column_width-2}s" % "Actual"}|#{column_names}"
	title_sep = "+#{"-"*(column_width-2)}+"
	for i in classes.keys do
		title_sep << "#{"-"*(column_width-1)}+"
	end
	puts title_sep
end

def create_row(table_width,column_width,classes,actual_id,confusion_row)
	row_str = "|#{"%-#{column_width-2}.#{column_width-2}s" % classes[actual_id]}|"
	confusion_row.each {|key,value| row_str << "#{"%-#{column_width-1}.#{column_width-1}s" % value}|"}
	puts row_str

	title_sep = "+#{"-"*(column_width-2)}+"
	for i in classes.keys do
		title_sep << "#{"-"*(column_width-1)}+"
	end
	puts title_sep
end

showusage unless ARGV.size == 2

test_file = ARGV[0]

predict_file = ARGV[1]

classes = { 1 => "CheerUp", 2 => "TossPaper",
			3 => "LineOnSofa", 4 => "Walking",
			5 => "StandUp", 6 => "SitDown"}

column_width = 12

table_width = classes.size*column_width + column_width

test_file_results = read_test_file test_file
predict_file_results = read_predict_file predict_file

confusionmatrix = calc_confustion classes,test_file_results,predict_file_results

create_table_header table_width,column_width,classes

confusionmatrix.each{ |key, value|
	create_row table_width,column_width,classes,key,value
}