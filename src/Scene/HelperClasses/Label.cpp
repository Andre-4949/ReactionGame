#include "../../../include/Scene/HelperClasses/Label.h"

Label makeLabelFromLine(std::string line){
    std::istringstream ss(line);

    int frame, trackId, truncated, occluded;
    float alpha, bboxLeft, bboxTop, bboxRight, bboxBottom;
    float height, width, length;
    float locationX, locationY, locationZ, rotationY;
    std::string type;

    ss >> frame >> trackId >> type >> truncated >> occluded >> alpha >> bboxLeft >> bboxTop >> bboxRight
     >> bboxBottom >> height >> width >> length >> locationX >> locationY >> locationZ >> rotationY;
    
    if (ss.fail()) {
        std::cerr << "Error reading line: " << line << std::endl;
        return Label();
    }
    
    GTBoundingBox bbox(static_cast<int>(bboxLeft), static_cast<int>(bboxTop),
   static_cast<int>(bboxRight - bboxLeft), static_cast<int>(bboxBottom - bboxTop));

    return Label(frame, type, bbox);
}

std::vector<Label> Label::loadLabelsFromFile(const std::string &filename) {
    std::vector<Label> labels;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open label file: " << filename << std::endl;
        return labels;
    }
    std::string line;
    Label currLabel;
    while (std::getline(file, line)) {
        currLabel = makeLabelFromLine(line);
        labels.push_back(currLabel);
    }
    return labels;
}

const std::string &Label::getMType() const {
    return m_type;
}

GTBoundingBox &Label::getBoundingBox() {
    return boundingBox;
}

int Label::getMFrame() const {
    return m_frame;
}
