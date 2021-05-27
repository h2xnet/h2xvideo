#ifndef H2XCORE_H2X_APPLICATION__H
#define H2XCORE_H2X_APPLICATION__H

#include <string>
#include "h2xcore/h2x_core_export.h"

namespace h2x {

class Config;

/*
 * ClassName: Application
 * Desc: Ӧ���࣬һ��Ӧ��ֻ������һ��ʵ��
 * Author: zfs
 * Date: 2021-05-16 17:12
 */
class H2XCORE_EXPORT Application {
public:
    Application(const Config* cfg);
    virtual ~Application();

    virtual 

	/*
	 * setName : ����Ӧ������
	 * Author: zfs
	 * Date: 2021-05-17 12:38
	 */
	void setName(const char* name, size_t nameSize) {
		if (name && nameSize > 0) {
			name_ = std::string(name, nameSize);
		}
		else {
			name_ = "h2xapp";
		}
	}

	/*
	 * getName: ��ȡӦ������
	 * Author: zfs
	 * Date: 2021-05-17 12:38
	*/
	const char* getName() {
		return name_.c_str();
	}

	/*
	 * FunctionName: getConfig
	 * Desc: ��ȡ����ָ��
	 * Author: zhaofushou
	 * Date: 2021-05-17 12:40
	 */
	Config* getConfig() const {
		return cfg_;
	}

private:
	// Ӧ������
	std::string name_;

	Config* cfg_;
};

} // end namespace h2x

#endif // !H2XCORE_H2X_APPLICATION__H
