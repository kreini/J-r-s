@app.route("/upload", methods=['POST'])
def upload_file():
    def custom_stream_factory(total_content_length, filename, content_type, content_length=None):
        import tempfile
        tmpfile = tempfile.NamedTemporaryFile('wb+', prefix='flaskapp', suffix='.nc')
        app.logger.info("start receiving file ... filename => " + str(tmpfile.name))
        return tmpfile

    import werkzeug, flask
    stream, form, files = werkzeug.formparser.parse_form_data(flask.request.environ, stream_factory=custom_stream_factory)
    for fil in files.values():
        app.logger.info(" ".join(["saved form name", fil.name, "submitted as", fil.filename, "to temporary file", fil.stream.name]))
        # Do whatever with stored file at `fil.stream.name`
    return 'OK', 200