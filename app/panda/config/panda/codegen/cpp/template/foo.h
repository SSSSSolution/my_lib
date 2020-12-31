$[head]#ifndef ${HEAD_DEFINE}_H
#define ${HEAD_DEFINE}_H
$[/head]#endif //${HEAD_DEFINE}_H

$[namespace]${NAME_SPACE} {
$[/namespace]}

$[class]class ${CLASS_NAME} {
    public:
        $[c]${CLASS_NAME}();
        $[d]~${CLASS_NAME}();
        $[vd]virtual ~${CLASS_NAME}();
        $[cc]${CLASS_NAME}(const ${CLASS_NAME} &other);
        $[a]${CLASS_NAME} &operator=(const ${CLASS_NAME} &other);
        $[mc]${CLASS_NAME}(${CLASS_NAME} &&other);
        $[ma]${CLASS_NAME} &operator=(const ${CLASS_NAME} &&other);
$[/class]};

