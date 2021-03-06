namespace Cooper {

	// Basic Template Engine
	class Template {
	protected:
		std::string content;
		std::map<std::string, std::string> data;

	public:

		// Reading file and save it into content
		void open(std::string name) {
			std::ifstream ifs("../src/Resources/views/" + name + ".tpl");
			std::string content( (std::istreambuf_iterator<char>(ifs) ),
		                       (  std::istreambuf_iterator<char>()  ) );
			this->content = content;
			return;
		}

		// Setting data
		void set(std::string name, std::string value) {
			this->data[name] = value;
		}

		// Concatenating data
		void add(std::string name, std::string value) {
			if (this->data.find(name) == this->data.end()) {
				this->set(name, "");
			}
			this->data[name].append(value);
		}

		// Render template into variable
		std::string render(bool header) {
			std::string _header = "Content-type: text/html\r\n\r\n";
			std::string _lcontent = this->content;

			for(std::map<std::string, std::string>::iterator it = this->data.begin(); it != this->data.end(); ++it) {
		        boost::algorithm::replace_all(_lcontent, "{{"+it->first+"}}", it->second);
		    }
		    if (header) {
		    	_header.append(_lcontent);
		    	return _header;
	    	} else {
	    		return _lcontent;
	    	}
		}

		std::string render() {
			return this->render(true);
		}

		// Template constructor
		Template(std::string name) {
			this->add("baseurl", Http::getBaseUrl());
			this->open(name);
		}
	};
}