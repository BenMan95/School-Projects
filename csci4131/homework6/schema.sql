-- Initialize contacts table
CREATE TABLE contact (
    id INT AUTO_INCREMENT,
    cname TEXT NOT NULL,
    email TEXT NOT NULL,
    mdate TIMESTAMP,
    meeting TEXT,
    soul BOOLEAN,
    PRIMARY KEY(id)
);

-- Initialize sales table
CREATE TABLE sale (
    sale_text TEXT NOT NULL,
    time_start TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    time_end TIMESTAMP
);
